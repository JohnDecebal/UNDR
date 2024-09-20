# UNDR AUTO: Automatic WDT Tool for Espresso

## Description

UNDR AUTO is a fully automatic WDT (Weiss Distribution Technique) tool designed for espresso enthusiasts. This open-source DIY project combines 3D printed parts with electronic and mechanical components to create a precise and customizable coffee distribution tool. By evenly distributing coffee grounds in the portafilter basket, UNDR AUTO aims to improve the consistency and quality of espresso shots.

## Key Features

- Fully automatic operation with proximity sensor activation
- Adjustable portafilter basket depth
- Variable speed control for vertical movement and distribution
- Customizable distribution patterns with 24 needle slots
- Wi-Fi control via onboard ESP32-S3 webserver
- Compact design with custom UNDR PCB

## Components Overview

The UNDR AUTO utilizes a mix of off-the-shelf and custom components:

- NEMA 17 Stepper Motors for precise movement
- Lead Screw System for vertical adjustment
- Custom 3D printed parts for the main structure
- UNDR PCB with ESP32-S3 for control and connectivity
- Various fasteners and electronic components

For a detailed list, please refer to the Bill of Materials (BOM) in this repository.

## Current Status and Limitations

**Important:** UNDR AUTO is currently in a prototype stage. Potential builders should be aware of the following:

1. Some 3D printed parts may require minor adjustments for proper fit.
2. The current wiring setup is not optimal and requires careful handling.
3. Assembly can be challenging, with some hard-to-reach fastening points.
4. The portafilter mount is specifically designed for Cafe Racer machines and will need modification for other models.
5. There's significant room for improvement in various aspects of the design.

We welcome contributions to address these limitations and enhance the overall design.

## Assembly Guide

Follow these detailed steps to assemble your UNDR AUTO:

1. **3D Printing:**
   - Print all parts listed in the "3D Printed Parts" section of the BOM.
   - Ensure prints are clean and free of defects. Sand parts if necessary for proper fit.
   - Pay special attention to the tolerances of connecting parts.

2. **Prepare the Main Body:**
   - Assemble the four parts of the main body, ensuring they fit snugly together.
   - Install M4 heated inserts into designated holes on the main body. Use a soldering iron to carefully melt the inserts into place.
   - Install 2 heated inserts on the lead screw mount.
   - Apply a strong adhesive to glue the grounds shield holder in place on the body. Ensure proper alignment before the glue sets.

3. **Motor and Lead Screw Installation:**
   - Attach the NEMA 17 stepper motor to the motor mount using M3 screws. Ensure the motor is securely fastened.
   - Install the lead screw system, carefully aligning it with the motor shaft. Use a coupling to connect the motor shaft to the lead screw.

4. **Carriage and Portafilter Mount Assembly:**
   - Install 4 bearings (ID 4mm x OD 8mm x Width 3mm) onto the carriage.
   - Attach the lead screw nut to the carriage using two M3 tapping screws.
   - Connect the portafilter mount to the leadscrew carriage. Note: This connection should be secure but allow for some movement to accommodate different portafilter sizes.

5. **Electronics Installation:**
   - Place the UNDR PCB in the designated space at the bottom of the tool. 
   - Note: The current design doesn't include mounting points for the PCB. Handle with care when moving the assembled unit.
   - Connect the ESP32-S3 to the PCB, ensuring all pins are properly aligned.
   - Install the proximity sensor.

6. **Wiring:**
   - Connect stepper motors to the PCB using the provided cables. Double-check the connections to ensure proper motor direction.
   - Carefully route all wires to avoid interference with moving parts.
   - Use cable ties or electrical tape to secure wires neatly along the frame of the device.

7. **Distributor Assembly:**
   - Assemble the distributor, magnetic connector, lid, arm, and cog.
   - Ensure the distributor spins freely and is properly aligned with the portafilter position.

8. **Lid Assembly:**
   - Assemble the lid using its 4 parts.
   - If desired, install small neodymium magnets in the provided slots for a satisfying close. Ensure polarity is correct for proper attraction to the main body.

9. **Tray Preparation:**
   - Glue magnets in place on the tray and corresponding spots on the body. This allows the tray to snap in place and be easily removed for cleaning.

10. **Final Assembly:**
    - Attach the assembled lid to the main body. Verify that it opens and closes smoothly.
    - Install the bottom lid, securing it with the appropriate screws.
    - Attach the threaded grounds shield to its glued holder, ensuring it's properly aligned with the distributor.

11. **Software Installation:**
    - Connect the ESP32 to your computer using a USB cable.
    - Download the latest firmware from the GitHub repository.
    - Use the Arduino IDE or your preferred ESP32 flashing tool to upload the code to the ESP32.
    - Verify that the upload was successful by checking for any error messages in the IDE.

12. **Testing and Calibration:**
    - Power on the device and connect to its Wi-Fi network (default SSID: "UNDR AUTO").
    - Access the web interface by navigating to 192.168.1.100 in your web browser.
    - Use the interface to test all movements: vertical travel, distribution rotation, and sensor activation.
    - Adjust settings as needed for your specific setup and preferences.

**Important Assembly Tips:**
- Use 90-degree allen wrenches for hard-to-reach fasteners, particularly in the main body assembly.
- Take your time and don't force parts together. If something doesn't fit, double-check the 3D print quality and sand if necessary.
- If using a portafilter other than Cafe Racer, you'll need to modify the mount design. Measure your portafilter carefully and adjust the 3D model accordingly.
- When gluing parts (like magnets or the grounds shield holder), ensure proper alignment before the glue sets.
- When flashing the code, make sure you have the correct board and port selected in your IDE.
- If you encounter any issues during the flashing process, double-check your connections and try resetting the ESP32.

Remember, this is a prototype design and you may encounter challenges during assembly. Don't hesitate to reach out to the community for support or share your improvement ideas!

## Usage Instructions

1. Connect to the UNDR AUTO Wi-Fi network
2. Access the web interface at 192.168.1.100
3. Configure settings (basket depth, speeds, rotation)
4. Place the filled portafilter on the mount
5. The device will automatically start the distribution process
6. Remove the portafilter and tamp as usual

Note: The current version does not support profile saving or live monitoring.

## Customization and Contribution

We strongly encourage users to customize the UNDR AUTO and contribute to its development. Here are some ways you can get involved:

### Customization

1. **Portafilter Mount:**
   - The current design is specific to Cafe Racer machines. We encourage users with different machines to create and share alternative designs.
   - When designing a new mount:
     - Carefully measure your portafilter's dimensions and unique features.
     - Use CAD software to modify the existing design or create a new one.
     - Consider factors like weight distribution and stability.
     - Share your designs with the community to help others with similar machines.

2. **Distribution Patterns:**
   - Experiment with different needle configurations in the 24 available slots.
   - Share your findings on how different patterns affect extraction.

3. **Software Tweaks:**
   - Modify the Arduino code to add new features or optimize existing ones.
   - If you create useful modifications, consider submitting them as pull requests.

### Contributing to the Project

We welcome contributions in various areas:

1. **Hardware Improvements:**
   - Refine the 3D printed parts for better fit and easier assembly.
   - Design solutions for improved wire management.
   - Develop a more secure method for attaching the portafilter mount to the leadscrew carriage.
   - Create a mounting solution for the PCB to prevent movement during operation.

2. **Software Enhancements:**
   - Implement profile saving and loading functionality in the web interface.
   - Add live monitoring capabilities for real-time adjustment during operation.
   - Develop over-the-air (OTA) firmware update functionality.
   - Create a mobile app for easier control and monitoring.

3. **Testing and Quality Assurance:**
   - Develop standardized testing procedures for assembled units.
   - Create a quality checklist for 3D printed parts.
   - Report bugs or suggest improvements based on your experience with the device.

### How to Contribute

1. Fork the repository on GitHub.
2. Create a new branch for your feature or bug fix.
3. Make your changes, ensuring they adhere to the project's coding standards.
4. Test your changes thoroughly.
5. Submit a pull request with a clear description of your changes and their benefits.
6. Engage in any feedback or discussion about your contribution.

### Community Guidelines

- Be respectful and constructive in all interactions.
- When reporting issues, provide as much detail as possible, including steps to reproduce.
- For major changes or new features, open an issue for discussion before submitting a pull request.
- Follow the project's coding style and documentation standards.
- Ensure all contributions are your own work or properly attributed.

Your contributions, no matter how small, are valuable to the project and the entire UNDR AUTO community. Together, we can create an exceptional tool for espresso enthusiasts worldwide!

## License

Copyright 2024 Ionut Decebal, UNDR COFFEE

This project is licensed under the CERN Open Hardware Licence Version 2 - Strongly Reciprocal (CERN-OHL-S v2). You may redistribute and modify this project under the terms specified at https://ohwr.org/cern_ohl_s_v2.txt.

This project is distributed WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING OF MERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS FOR A PARTICULAR PURPOSE. Please see the CERN-OHL-S v2 for applicable conditions.

## Acknowledgments and Contact

- Inspired by WDT techniques discussed on r/espresso
- Thanks to all contributors and testers

For questions or support, contact:
John Decebal - undr.coffee@gmail.com

Project Repository: [https://github.com/JohnDecebal/UNDR](https://github.com/JohnDecebal/UNDR)
