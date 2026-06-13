# Project Architecture

This is a C++ Vulkan application with:

- Source code in `/game/src`
- Asset files in `/game/assets`


## Coding Standards

- Use C++ for all new files
- Follow the existing naming conventions
  - Variable names are all lowercase with underscore separators
  - Function names use camelCase
- Do not use `auto` instead use the actual type
  - e.g. `for (const auto& device)` would become `for (const VkPhysicalDevice& device)`
