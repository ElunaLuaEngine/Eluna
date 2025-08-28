<div align="center">

# [![mod-eluna](src/LuaEngine/docs/Eluna.png)](https://github.com/azerothcore/mod-eluna)

*Unleash the power of Lua scripting in your AzerothCore server*

[![Discord](https://img.shields.io/badge/Discord-Join%20Us-7289DA?style=for-the-badge&logo=discord&logoColor=white)](https://discord.com/invite/ZKSVREE7)
[![Lua](https://img.shields.io/badge/Lua-5.2-2C2D72?style=for-the-badge&logo=lua&logoColor=white)](http://www.lua.org/manual/5.2/)
[![AzerothCore](https://img.shields.io/badge/AzerothCore-Integrated-darkgreen?style=for-the-badge)](http://www.azerothcore.org/)

---
</div>

> [!IMPORTANT]
> **mod-eluna** is an independent Lua scripting engine specifically designed for AzerothCore. This project has **diverged from the original Eluna project** and is no longer compatible with standard Eluna scripts. Scripts written for mod-eluna will not work with the original Eluna engine and vice versa.

## 🚀 Overview

mod-eluna is a powerful, AzerothCore-specific implementation of a Lua scripting engine that enables server administrators and developers to create custom gameplay features, events, and mechanics without modifying the core server code.

### Key Features
- **Native AzerothCore Integration**: Built specifically for AzerothCore's architecture
- **Enhanced API**: Extended functionality for AzerothCore, beyond the original Eluna specification.
- **Community-Driven Development**: Actively maintained with community contributions

## ⚠️ Compatibility Notice

### mod-eluna vs Original Eluna

**mod-eluna is NOT compatible with the original Eluna project.** This fork has evolved independently with AzerothCore-specific enhancements and API changes that make scripts non-interchangeable.

### For Original Eluna Compatibility

If you need to use standard Eluna scripts or maintain compatibility with the original Eluna project, please use the dedicated AzerothCore port available at:

**🔗 [ElunaAzerothCore](https://github.com/Eluna-Ports/ElunaAzerothCore)**

This repository maintains compatibility with the original Eluna API and supports standard Eluna scripts.

## 📋 Table of Contents

- [Installation](#-installation)
- [Documentation](#-documentation)
- [API Reference](#api-reference)
- [Support](#-support)
- [Contributing](#-contributing)
- [Acknowledgements](#-acknowledgements)

## ⚡ Installation

### Prerequisites
- AzerothCore server installation
- Git version control system
- CMake build system

### Installation Steps

```bash
# Navigate to your AzerothCore modules directory
cd <azerothcore-path>/modules

# Clone the mod-eluna repository
git clone https://github.com/azerothcore/mod-eluna.git

# Configure build with your preferred Lua version
cd <azerothcore-build-directory>
cmake ../ -DLUA_VERSION=luajit  # Options: luajit, lua52, lua53, lua54

# Default: If no version is specified, Lua 5.2 will be used

# Rebuild your AzerothCore server
make -j$(nproc)
```

### Supported Lua Versions
- **LuaJIT** (Recommended for performance)
- **Lua 5.2** (Default)
- **Lua 5.3**
- **Lua 5.4**

## 📚 Documentation

### Getting Started
- [Installation Guide](https://github.com/azerothcore/mod-eluna/tree/master/docs/USAGE.md)
- [Implementation Details](https://github.com/azerothcore/mod-eluna/tree/master/docs/IMPL_DETAILS.md)

### API Reference
- **[mod-eluna API Documentation](https://www.azerothcore.org/eluna/)** - Complete API reference for mod-eluna
- **[Hooks Documentation](https://github.com/azerothcore/mod-eluna/blob/master/src/LuaEngine/Hooks.h)** - Available event hooks
- **[Lua 5.2 Reference](http://www.lua.org/manual/5.2/)** - Official Lua language documentation

> [!WARNING]
> **API Differences**: mod-eluna functions may not be available in the original Eluna project and vice versa. Always refer to the mod-eluna specific documentation when developing scripts.

## 💬 Support

### Getting Help
- **GitHub Issues**: [Report bugs or request features](https://github.com/azerothcore/mod-eluna/issues)
- **Discord Community**: [Join our Discord server](https://discord.com/invite/bx3y5Qmy)
- **AzerothCore Discord**: [Official AzerothCore support](http://www.azerothcore.org/)

### Resources
- [Lua Programming Guide](http://www.lua.org/)
- [AzerothCore Documentation](http://www.azerothcore.org/)

## 🤝 Contributing

We welcome contributions from the community! Here's how you can help:

### Development Workflow
```mermaid
graph LR
    A[Fork Repository] --> B[Create Branch]
    B --> C[Make Changes]
    C --> D[Submit PR]
    D --> E[Review Process]
```

### Contribution Guidelines
1. **Fork** the repository
2. **Create** a feature branch from `master`
3. **Implement** your changes with proper testing
4. **Follow** the existing code style and conventions
5. **Submit** a pull request with a clear description

## 🌟 Acknowledgements

### Original Project
mod-eluna is built upon the foundation of the original [Eluna](https://github.com/ElunaLuaEngine/Eluna) project. We acknowledge and thank the original Eluna team for their pioneering work in Lua scripting for World of Warcraft server emulators.

### Related Projects
- **[Original Eluna Repository](https://github.com/ElunaLuaEngine/Eluna)** - The original Eluna project
- **[Eluna Discord Community](https://discord.gg/bjkCVWqqfX)** - Original Eluna community support
- **[ElunaAzerothCore](https://github.com/Eluna-Ports/ElunaAzerothCore)** - AzerothCore with original Eluna compatibility

### Supported Emulators
- **[AzerothCore](http://www.azerothcore.org/)** - Primary target (this project)
- **[TrinityCore](https://www.trinitycore.org/)** - Original Eluna support
- **[MaNGOS](https://www.getmangos.eu/)**
- **[cMaNGOS](https://cmangos.net/)**

## 📄 License

This project is licensed under the GNU General Public License v3.0. See [LICENSE](https://github.com/azerothcore/mod-eluna/blob/master/LICENSE) for details.

---

<div align="center">
<sub>Developed with ❤️ by the AzerothCore and mod-eluna community</sub>

[⬆ Back to Top](#-overview)
</div>
