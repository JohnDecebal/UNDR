# UNDR AUTO: Automatic WDT Tool for Espresso

## Description

UNDR AUTO is a fully automatic WDT (Weiss Distribution Technique) tool designed for espresso enthusiasts. This DIY project combines 3D printed parts with electronic and mechanical components to create a precise and customizable coffee distribution tool.

The UNDR AUTO is designed to improve the consistency and quality of espresso shots by evenly distributing coffee grounds in the portafilter basket, a crucial step in espresso preparation.

## Features

- Fully automatic operation
- Adjustable portafilter basket depth accommodation
- Variable speed control for portafilter vertical movement
- Adjustable distributor speed up to 1000 RPM
- 24 available needle slots for customizable distribution patterns
- Wi-Fi control via a webserver hosted on the onboard ESP32-S3
- UNDR PCB for advanced control and customization
- Proximity sensor for automatic operation

## Bill of Materials

For a detailed list of all required components, please refer to the [Bill of Materials](link-to-bom-file.md).

Key components include:
- NEMA 17 Stepper Motors
- Lead Screw System
- Various 3D printed parts
- Fasteners (M2, M3, and M4 screws and inserts)
- Electronic components (UNDR PCB with ESP32-S3, proximity sensor)

## Current Limitations and Challenges

**Important Notice:** The UNDR AUTO is currently in a prototype stage and is not a finished product. Potential builders should be aware of the following limitations and challenges:

1. **Imperfect Tolerances:** Some of the 3D printed parts may not fit together perfectly. Users might need to sand certain parts to achieve a proper fit.

2. **Wiring Issues:** The current design has some loose wires that are wrapped around components. This is not ideal and may require careful handling during assembly and operation.

3. **Awkward Fastening:** Some parts are fastened in ways that can be difficult to access. Users will need 90-degree tools (such as allen wrenches) to properly assemble certain sections of the device.

4. **Portafilter Mount Attachment:** The attachment of the portafilter mount to the leadscrew carriage is currently very temperamental. Users may need to experiment with different approaches to secure this connection reliably.

5. **Portafilter Compatibility:** The current portafilter mount is designed specifically for a Cafe Racer portafilter. Users with different espresso machines will need to modify this part to fit their particular portafilter.

6. **Assembly Complexity:** Due to the prototype nature of the design, assembly can be challenging and may require problem-solving skills and patience.

7. **Potential for Improvements:** As this is an ongoing project, there's significant room for improvement in various aspects of the design and functionality.

We appreciate your understanding and patience with these issues. Contributions and suggestions for improvements are welcome and encouraged.

## Assembly Instructions

For detailed assembly instructions, including a step-by-step build video, please visit our website:

[UNDR Coffee Build Instructions](https://undr.coffee)

The video guide will walk you through the entire assembly process, from 3D printing the components to the final setup of your UNDR AUTO. Please pay special attention to the sections addressing the challenges mentioned above.

Additional Assembly Tips:
- Have sandpaper on hand to adjust tolerances where needed.
- Use cable ties or electrical tape to secure loose wires.
- A set of 90-degree allen wrenches will be invaluable for accessing hard-to-reach fasteners.
- Take your time and don't force parts together if they don't fit easily.
- When attaching the portafilter mount to the leadscrew carriage, be patient and prepared to try different approaches to achieve a secure connection.
- If you're not using a Cafe Racer portafilter, be prepared to modify the portafilter mount design to fit your specific machine.

## Usage

Once assembled, the UNDR AUTO can be used as follows:

1. Connect to the same Wi-Fi network as your UNDR AUTO.
2. Access the web interface by navigating to 192.168.1.100 in your web browser.
3. Use the web interface to configure your settings:
   - Adjust the portafilter basket depth
   - Set the speed for the portafilter's vertical movement
   - Adjust the distributor RPM (up to 1000 RPM)
   - Set the rotation amount and direction
4. Place your filled portafilter on the mount.
5. The proximity sensor will detect the portafilter and start the distribution process automatically.
6. Once complete, remove your portafilter and tamp as usual.

(Add any additional steps or tips for optimal use)

## Wi-Fi Control

The UNDR AUTO features a built-in web server hosted on the ESP32-S3, allowing for control via Wi-Fi:

1. Ensure your device (smartphone, tablet, or computer) is connected to the same Wi-Fi network as the UNDR AUTO.
2. Open a web browser and navigate to 192.168.1.100.
3. Use the web interface to adjust the following parameters:
   - Speed: Control the speed of the distribution process
   - Depth: Set the depth for the portafilter basket
   - Rotation amount: Determine how much the distributor rotates
   - Rotation direction: Choose clockwise or counterclockwise rotation

Note: The current version does not support live monitoring or saving distribution profiles. These features may be added in future updates.

## Customization

Given the specific compatibility of the current portafilter mount, many users will need to customize this part. Here are some tips for modifying the portafilter mount:

1. Measure your portafilter carefully, paying special attention to the diameter and any unique features that might affect mounting.
2. Use CAD software to modify the existing design, or create a new design from scratch based on your measurements.
3. Consider printing several prototypes to test the fit before finalizing your design.
4. Share your modified designs with the community to help others with similar machines.

## Contributing

Given the current state of the project, contributions to improve the design or functionality are especially welcome. Areas that could benefit from improvement include:
- Refining tolerances for 3D printed parts
- Improving wire management
- Redesigning fastening methods for easier assembly
- Enhancing the portafilter mount attachment mechanism
- Creating alternative portafilter mount designs for popular espresso machines
- Enhancing the overall user experience

Please follow these steps to contribute:

1. Fork the repository
2. Create a new branch (`git checkout -b feature/ImprovementName`)
3. Commit your changes (`git commit -m 'Add some ImprovementName'`)
4. Push to the branch (`git push origin feature/ImprovementName`)
5. Open a Pull Request

## License

(Specify the license under which you're releasing this project, e.g., MIT, GPL, etc.)

## Acknowledgments

- Inspired by WDT techniques discussed on r/espresso
- Thanks to all contributors and testers

## Contact

Your Name - [@your_twitter](https://twitter.com/your_username) - email@example.com

Project Link: [https://github.com/your_username/undr-auto](https://github.com/your_username/undr-auto)
