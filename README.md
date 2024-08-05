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
- UNDR PCB for reduced size and component quantity
- Proximity sensor for automatic operation

## Bill of Materials

For a detailed list of all required components, please refer to the BOM file.

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

Follow these steps to assemble your UNDR AUTO:

1. **3D Printing:**
   - Print all required parts listed in the "3D Printed Parts" section of the Bill of Materials.
   - Ensure prints are clean and free of defects. Sand parts if necessary for proper fit.

2. **Prepare the Main Body:**
   - Assemble the four parts of the main body.
   - Install M4 heated inserts into designated holes on the main body.
   - Install 2 heated inserts on the lead screw mount.
   - Glue the grounds shield holder in place on the body at this stage.

3. **Motor and Lead Screw Installation:**
   - Attach the NEMA 17 stepper motor to the motor mount using M3 screws.
   - Install the lead screw system, ensuring proper alignment with the motor.

4. **Carriage and Portafilter Mount Assembly:**
   - Install 4 bearings and the lead screw nut on the carriage using two tapping screws.
   - Attach the portafilter mount to the leadscrew carriage.
   - Note: Ensure the connection between the portafilter mount and carriage is secure but loose enough to allow free up and down movement.

5. **Electronics Installation:**
   - Place the UNDR PCB in the designated space at the bottom of the tool. Note: The PCB doesn't have mounting points yet, so it will rest freely in this space.
   - Connect the ESP32-S3 to the PCB.
   - Install the proximity sensor in its designated location.

6. **Wiring:**
   - Connect stepper motors to the PCB using the provided cables.
   - Secure all wires neatly, using cable ties or electrical tape as needed.

7. **Distributor Assembly:**
   - Assemble the distributor, magnetic connector, lid, arm, and cog.

8. **Lid Assembly:**
   - Assemble the lid separately using its 4 parts.
   - If desired, install magnets in the provided slots for a satisfying close.

9. **Tray Preparation:**
   - Glue magnets in place on the tray and corresponding spots on the body. This allows the tray to snap in place and be easily removed for cleaning.

10. **Final Assembly:**
    - Attach the assembled lid to the main body. Note that it's designed to be easily removable.
    - Install the bottom lid.
    - Attach the threaded grounds shield to its glued holder.

11. **Code Flashing:**
    - Once the tool is fully assembled, connect the ESP32 to your computer using a USB cable.
    - Download the latest firmware from our GitHub repository.
    - Use the Arduino IDE or your preferred ESP32 flashing tool to upload the code to the ESP32.
    - Verify that the upload was successful.

12. **Testing and Calibration:**
    - Power on the device and connect to its Wi-Fi network.
    - Access the web interface to test all movements and adjust settings as needed.
    - Ensure all functions are working correctly after flashing the code.

**Important Assembly Tips:**
- Use 90-degree allen wrenches for hard-to-reach fasteners.
- Take your time and don't force parts together.
- If using a portafilter other than Cafe Racer, modify the mount design accordingly.
- Refer to the Bill of Materials for specific screw sizes and quantities.
- When gluing parts (like magnets or the grounds shield holder), ensure proper alignment before the glue sets.
- The loose fit of the PCB is intentional in the current design. Handle with care when moving the assembled unit.
- When flashing the code, make sure you have the correct board and port selected in your IDE.
- If you encounter any issues during the flashing process, double-check your connections and try resetting the ESP32.

Remember, this is a prototype design and you may encounter challenges during assembly. Don't hesitate to reach out to the community for support or share your improvement ideas!

## Usage

Once assembled, the UNDR AUTO can be used as follows:

1. Connect to the UNDR AUTO network.
2. Access the web interface by navigating to 192.168.1.100 in your web browser.
3. Use the web interface to configure your settings:
   - Adjust the portafilter basket depth
   - Set the speed for the portafilter's vertical movement
   - Adjust the distributor RPM (up to 1000 RPM)
   - Set the rotation amount and direction
4. Place your filled portafilter on the mount.
5. The proximity sensor will detect the portafilter and start the distribution process automatically.
6. Once complete, remove your portafilter and tamp as usual.

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

This project is open source and available under the GNU General Public License v3.0 (GPL-3.0).
Copyright (c) 2024 John Decebal, UNDR COFFEE
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see https://www.gnu.org/licenses/.
Note: This license applies to both the software and hardware designs in this project.
For the full license text, please see the LICENSE file in this repository or visit https://www.gnu.org/licenses/gpl-3.0.en.html.

## Acknowledgments

- Inspired by WDT techniques discussed on r/espresso
- Thanks to all contributors and testers

## Contact

Your Name - [@your_twitter](https://twitter.com/your_username) - email@example.com

Project Link: [https://github.com/your_username/undr-auto](https://github.com/your_username/undr-auto)
