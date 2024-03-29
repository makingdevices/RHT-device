<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Instagram][ig-shield]][ig-url]
[![PCBWAY][sponsor-shield]][sponsor-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![LinkedIn][linkedin-shield]][linkedin-url]


<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://makingdevices.com/links/">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Making Devices</h3>

  <p align="center">
    Open Source projects where we struggle with engineering, electronics, coding and who knows what else... In this case, RHT Device is a very simple humidity and temperature sensor, so hopefully you may find it interesting ;)
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#Build-one">Build one</a>
      <ul>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#Sponsor">Sponsor</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![Bytes Counter Shot][product-screenshot]](https://github.com/makingdevices/RHT-device)

RHT Device is a very simple relative humidity and temperature sensor that shows the data in the screen. The project was chosen to test the I2C communication of the PIC18F14k50. 

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

[![Microcontroller][PIC]][PIC-url]
[![MPLAB C][MPLAB-C]][MPLAB-C-url]
[![Kicad][kicad-shield]][kicad-url]
[![SPONSOR][sponsor-icon]][sponsor-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->

## Build one
Documentation is being updated.

1. Get the gerber files for the latest version: [V1.0](https://github.com/makingdevices/RHT-device/tree/main/Gerber/Gerber_v1.0.zip) 
2. Send them to a PCB manufacturer ([Our Sponsor is PCBWAY][sponsor-url])
3. You should solder all the components in the board. ([The schematic is available here v1.0][schematic-url])
4. Program the firmware into the pic. ([V1.0 is here][firmware-url])

Enjoy :)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->
## Usage

Instructions of use:

- When the button is pressed, the temperature is shown.
- Next time the button is pressed, relative humidity is shown. It will change between temperature and humidity
- After 10s of no use, the screen will be off and the device enters sleep mode.
- One button click will wake up the device for another 10s

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ROADMAP -->
## Roadmap

- [x] Finish the firmware for the PIC18F14K50
- [x] Validate the RHT-Device board V1.0
- [x] Update all the documentation


See the [open issues](https://github.com/makingdevices/RHT-device/issues) for a full list of proposed features (and known issues).

State: Project <b>FINISHED</b> - 11/05/2023

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Power Consumption -->
## Power Consumption

One of the main requisites for the board is to obtain a minimum power consumption so the device can live from a coin cell. When the screen is on we obtain:

[![ON Screen consumption Shot][pconscreen-screenshot]](https://github.com/makingdevices/RHT-device/tree/main/Validation/)

<b>Average Current</b> = 10.69mA

In sleep mode, the power consumption is as follows:

[![OFF Screen consumption Shot][pcoffscreen-screenshot]](https://github.com/makingdevices/RHT-device/tree/main/Validation/)

<b>Average Current</b> = 6.79uA

With this data and a normal use of 5 reading a day, the battery should last for several years.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- LICENSE -->
## License

Distributed under three licenses:
- [Hardware](/License/HW_cern_ohl_s_v2.pdf)
- [Software](/License/SW_GPLv3.0.txt)
- [Documentation](/License/Documentation_CC-BY-SA-4.0.txt)

[![GPL v3 License][license-shield]][license-url] 
<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Making Devices - [@MakingDevices](https://www.instagram.com/makingdevices/)

Project Link: [https://github.com/makingdevices/Thermo-device-logger](https://github.com/makingdevices/RHT-device/)

Other Links: [LinkTree](https://makingdevices.com/links/)


<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Sponsor -->
## Sponsor

[PCBWAY](https://www.pcbway.com/?from=makingdevices) is the most professional PCB manufacturer for prototyping and low-volume production to work with in the world. With more than a decade in the field, They are committed to meeting the needs of their customers from different industries in terms of quality, delivery, cost-effectiveness and any other demanding requests. As Sponsor of Making Devices, they will be in charge of all the PCBs for MDV, allowing both of us to grow together in a long term partnership. We hope you take them into account for your both personal and professional prototypes or products.

[![Sponsor Shot][sponsor-screenshot-pcb1]][sponsor-url]
[![Sponsor Shot][sponsor-screenshot-pcb2]][sponsor-url]


<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/makingdevices/RHT-device.svg?style=for-the-badge
[contributors-url]: https://github.com/makingdevices/RHT-device/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/makingdevices/RHT-device.svg?style=for-the-badge
[forks-url]: https://github.com/makingdevices/RHT-device/network/members
[stars-shield]: https://img.shields.io/github/stars/makingdevices/RHT-device.svg?style=for-the-badge
[stars-url]: https://github.com/makingdevices/RHT-device/stargazers
[issues-shield]: https://img.shields.io/github/issues/makingdevices/RHT-device.svg?style=for-the-badge
[issues-url]: https://github.com/makingdevices/RHT-device/issues
[license-shield]: /images/license.png
[license-url]: https://github.com/makingdevices/RHT-device/tree/main/License
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/company/making-devices/
[sponsor-shield]: https://img.shields.io/badge/SPONSOR-PCBWAY-black.svg?style=for-the-badge&colorB=1200
[sponsor-url]: https://www.pcbway.com/?from=makingdevices
[sponsor-screenshot-pcb1]: /images/rht_pcb1.jpg
[sponsor-screenshot-pcb2]: /images/rht_pcb2.jpg
[product-screenshot]: images/screenshotV1.0.gif
[pconscreen-screenshot]: /Validation/4_Power_Consumption/Screen_ON.png
[pcoffscreen-screenshot]: /Validation/4_Power_Consumption/Screen_OFF.png
[PIC]: https://img.shields.io/badge/PIC18LF14K50-000000?style=for-the-badge
[PIC-url]: http://ww1.microchip.com/downloads/en/devicedoc/40001350f.pdf
[kicad-shield]: https://img.shields.io/badge/kicad-0b03fc?style=for-the-badge&logo=kicad&logoColor=white
[kicad-url]: https://www.kicad.org/
[YT-screenshot]: images/YT_assembly.PNG
[sponsor-icon]:  https://img.shields.io/badge/-PCBWAY-black.svg?style=for-the-badge&colorB=1200
[ig-shield]: https://img.shields.io/badge/instagram-a83297?style=for-the-badge&logo=instagram&logoColor=white
[ig-url]: https://www.instagram.com/makingdevices/
[MPLAB-C]: https://img.shields.io/badge/MPLAB%20C18-DD0031?style=for-the-badge&logo=C&logoColor=white
[MPLAB-C-url]: https://www.microchip.com/en-us/development-tool/SW006011
[Svelte.dev]: https://img.shields.io/badge/Svelte-4A4A55?style=for-the-badge&logo=svelte&logoColor=FF3E00
[Svelte-url]: https://svelte.dev/
[Laravel.com]: https://img.shields.io/badge/Laravel-FF2D20?style=for-the-badge&logo=laravel&logoColor=white
[Laravel-url]: https://laravel.com
[Bootstrap.com]: https://img.shields.io/badge/Bootstrap-563D7C?style=for-the-badge&logo=bootstrap&logoColor=white
[Bootstrap-url]: https://getbootstrap.com
[JQuery.com]: https://img.shields.io/badge/jQuery-0769AD?style=for-the-badge&logo=jquery&logoColor=white
[JQuery-url]: https://jquery.com 
[schematic-url]: /Output_PDF/Schematic_v1.0.pdf
[firmware-url]: /Firmware/RHT-device.hex