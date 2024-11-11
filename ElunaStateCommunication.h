#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "lua.hpp"

// Message structure for passing events
struct Message {
    int mapId;                   // The ID of the map where the event is triggered
    std::string eventName;        // Name of the event being triggered
    std::string data;             // Data passed with the event
};

// Thread-safe message queue for asynchronous event handling
class MessageQueue {
public:
    // Push a new message into the queue
    void push(const Message& msg);
    
    // Pop a message from the queue, blocking until a message is available
    Message pop();
    
    // Check if the queue is empty
    bool empty();

private:
    std::queue<Message> queue_;               // Internal queue to hold messages
    std::mutex mutex_;                        // Mutex for thread-safe access to the queue
    std::condition_variable condition_;       // Condition variable to wait for new messages
};

class ElunaStateCommunication
{
public:
    // Register the Lua functions in the Lua state
    static void Register(lua_State* L);

    // Lua function to register a state event
    static int RegisterStateEvent(lua_State* L);
    
    // Lua function to notify an event
    static int NotifyStateEvent(lua_State* L);

    // Update function to process all registered events for all maps
    static void Update(lua_State* L);

private:
    // Map of event handlers, indexed by mapId and event name
    static std::unordered_map<int, std::unordered_map<std::string, std::function<void(std::string)>>> eventHandlers;

    // Message queue for asynchronous event handling
    static MessageQueue messageQueue;

    // Process all messages for a specific mapId
    static void ProcessMessages(lua_State* L, int mapId);
};
