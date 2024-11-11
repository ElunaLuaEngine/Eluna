#include "ElunaStateCommunication.h"
#include <iostream>

// Static member definitions
std::unordered_map<int, std::unordered_map<std::string, std::function<void(std::string)>>> ElunaStateCommunication::eventHandlers;
MessageQueue ElunaStateCommunication::messageQueue;

void ElunaStateCommunication::Register(lua_State* L)
{
    // Register Lua functions: 'RegisterStateEvent' and 'NotifyStateEvent'
    lua_register(L, "RegisterStateEvent", ElunaStateCommunication::RegisterStateEvent);
    lua_register(L, "NotifyStateEvent", ElunaStateCommunication::NotifyStateEvent);
}

int ElunaStateCommunication::RegisterStateEvent(lua_State* L)
{
    // Get the mapId from the first argument
    int mapId = luaL_checkint(L, 1);

    // Get the event name from the second argument
    const char* eventName = luaL_checkstring(L, 2);
    
    // Ensure the third argument is a function (callback)
    if (!lua_isfunction(L, 3)) {
        luaL_error(L, "Expected a function as the third argument");
        return 0;
    }

    // Store a reference to the Lua callback function
    lua_pushvalue(L, 3);
    int callbackRef = luaL_ref(L, LUA_REGISTRYINDEX);

    // Save the callback in the event handler map for this mapId and eventName
    eventHandlers[mapId][eventName] = [L, callbackRef](std::string data) {
        // Retrieve the callback function from Lua's registry
        lua_rawgeti(L, LUA_REGISTRYINDEX, callbackRef);
        // Pass the event data as an argument to the Lua function
        lua_pushstring(L, data.c_str());
        // Call the Lua function with 1 argument and expect 0 results
        lua_call(L, 1, 0);
    };

    return 0;  // Return 0 to Lua (no results)
}

int ElunaStateCommunication::NotifyStateEvent(lua_State* L)
{
    // Get the mapId from the first argument
    int mapId = luaL_checkint(L, 1);

    // Get the event name from the second argument
    const char* eventName = luaL_checkstring(L, 2);

    // Get the event data from the third argument
    const char* data = luaL_checkstring(L, 3);

    // Add the event to the message queue for asynchronous processing
    messageQueue.push({mapId, eventName, data});

    return 0;  // Return 0 to Lua (no results)
}

// This method processes all messages for a specific mapId
void ElunaStateCommunication::ProcessMessages(lua_State* L, int mapId)
{
    // Loop to process all available messages
    while (!messageQueue.empty()) {
        // Get the next message from the queue
        Message msg = messageQueue.pop();

        // Check if there are any event handlers registered for this mapId and eventName
        if (eventHandlers.find(msg.mapId) != eventHandlers.end() &&
            eventHandlers[msg.mapId].find(msg.eventName) != eventHandlers[msg.mapId].end()) {
            // Call the registered callback with the event data
            eventHandlers[msg.mapId][msg.eventName](msg.data);
        }
    }
}

// This method processes events for all registered maps
void ElunaStateCommunication::Update(lua_State* L)
{
    // Iterate over all registered mapId's that have event handlers
    for (const auto& mapEvents : eventHandlers) {
        int mapId = mapEvents.first;
        // Process messages for each mapId
        ProcessMessages(L, mapId);
    }
}

// Push a new message into the queue and notify any waiting threads
void MessageQueue::push(const Message& msg)
{
    {  // Critical section starts here
        std::lock_guard<std::mutex> lock(mutex_);   // Lock the mutex for thread-safety
        queue_.push(msg);                           // Add the message to the queue
    }  // Mutex is automatically released when lock goes out of scope

    condition_.notify_one();  // Notify one waiting thread that a message is available
}

// Pop a message from the queue, blocking if necessary until a message is available
Message MessageQueue::pop()
{
    std::unique_lock<std::mutex> lock(mutex_);
    condition_.wait(lock, [this]() { return !queue_.empty(); });  // Wait until there is a message available

    Message msg = queue_.front();  // Get the message at the front of the queue
    queue_.pop();                  // Remove the message from the queue
    return msg;                    // Return the message
}

// Check if the queue is empty (used for the update loop)
bool MessageQueue::empty()
{
    std::lock_guard<std::mutex> lock(mutex_);   // Lock the mutex to ensure thread-safety
    return queue_.empty();                      // Return whether the queue is empty
}
