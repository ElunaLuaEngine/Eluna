## How to Add Custom Methods

You can extend the available methods by creating a directory named `Custom` in the `Methods` directory, and adding a header file named `CustomMethods.h` inside it.

Once this file is added, re-run cmake and recompile.

## Example: `Custom/CustomMethods.h`

```cpp
#include "ElunaTemplate.h"
#include "ElunaIncludes.h"

#ifndef CUSTOMMETHODS_H
#define CUSTOMMETHODS_H

namespace LuaCustom
{
    // Define a custom method that returns the players name
    int CustomPlayerMethod(Eluna* E, Player* player)
    {
        E->Push(player->GetName());
        return 1;
    }

    // Create a custom player method registry
    ElunaRegister<Player> CustomPlayerMethods[] =
    {
        // Add the custom player method to the registry
        { "CustomPlayerMethod", &LuaCustom::CustomPlayerMethod },
    };

    inline void RegisterCustomMethods([[maybe_unused]] Eluna* E)
    {
        // Append all the custom Player methods to the Player object
        ElunaTemplate<Player>::SetMethods(E, CustomPlayerMethods);
    };
};

#endif
```