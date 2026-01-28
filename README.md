# 🕌 Zakat Calculator on ESP8266

> **A fully-featured Islamic Zakat calculator running on a $4 microcontroller, self-hosted from home without port forwarding or hosting costs.**

![ESP8266](https://img.shields.io/badge/ESP8266-Powered-blue)
![Self Hosted](https://img.shields.io/badge/Self--Hosted-Free-green)
![No Port Forwarding](https://img.shields.io/badge/No%20Port%20Forwarding-Required-orange)

## 🎯 What Makes This Special?

This project demonstrates how to host a **public web server** on a **$4 Wemos D1 Mini (ESP8266)** microcontroller from your home—**completely free**, with **no hosting fees**, **no cloud services**, and **no need for real IP or port forwarding**.

This solution offers:
- ✅ **Zero hosting costs** (after the $4 hardware purchase)
- ✅ **Self-hosted** from your home network
- ✅ **No port forwarding** required
- ✅ **Always online** (uses ~0.5W of power)
- ✅ **Full control** over your data and infrastructure

### 💡 Learning About:
- IoT web hosting
- ESP8266 development
- Self-hosting without cloud dependencies
- Embedded web servers
- WiFi-based microcontroller projects

---

## 📸 Demo

**Live Demo**: [Coming Soon - Running on ESP8266 in my home!]

![Setup Photo](./setup-photo.jpg)
*The actual ESP8266 board running this calculator 24/7 from my home*

### Features:
- 🌙 **Dark Mode Support** - Automatic system detection
- 🌍 **Multi-language** - English, Arabic, Bengali, Hindi
- 💰 **Complete Zakat Calculation** - Assets, liabilities, Nisab threshold
- 📱 **Responsive Design** - Works on all devices
- 🖨️ **Print Reports** - Generate printable Zakat reports
- ⚡ **Real-time Updates** - Instant calculations as you type
- 🎨 **Modern UI** - Built with Tailwind CSS

---

## 🛠️ Hardware Requirements

| Component | Specification |
|-----------|--------------|
| **Microcontroller** | Wemos D1 Mini (ESP8266) |
| **Power Supply** | 5V Micro USB cable |

**That's it!** No expensive servers, no monthly fees.

### Optional:
- Case/enclosure for the board
- USB power adapter (you probably have one already)

---

## 📋 Software Requirements

- **Arduino IDE** (1.8.x or 2.x)
- **ESP8266 Board Support** (via Board Manager)
- **Required Libraries:**
  - `ESP8266WiFi`
  - `ESPAsyncTCP`
  - `ESPAsyncWebServer`
  - `LittleFS`
  - `WiFiManager`

---

## 🚀 Installation

### Step 1: Set Up Arduino IDE

1. **Install Arduino IDE**
   - Download from [arduino.cc](https://www.arduino.cc/en/software)

2. **Add ESP8266 Board Support**
   - Open Arduino IDE
   - Go to `File` → `Preferences`
   - Add this URL to "Additional Board Manager URLs":
     ```
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
     ```
   - Go to `Tools` → `Board` → `Boards Manager`
   - Search for "ESP8266" and install

3. **Install Required Libraries**
   - Go to `Sketch` → `Include Library` → `Manage Libraries`
   - Install the following:
     - **ESPAsyncTCP** by Me-No-Dev
     - **ESPAsyncWebServer** by Me-No-Dev
     - **WiFiManager** by tzapu

### Step 2: Prepare the Code

1. **Clone this repository**
   ```bash
   git clone https://github.com/sharf-shawon/ZakatCalc.git
   cd ZakatCalc
   ```

2. **Open `ZakatCalc.ino`** in Arduino IDE

3. **Update the HTML** (Optional - if you modified `index.html`)
   - Minify the `index.html` file using any online HTML minifier
   - Replace the content of `zakat_html[]` in the `.ino` file with the minified HTML

### Step 3: Upload to ESP8266

1. **Connect your Wemos D1 Mini** via USB

2. **Select the correct board**
   - Go to `Tools` → `Board` → `ESP8266 Boards` → `LOLIN(WEMOS) D1 R2 & mini`

3. **Configure settings**
   - Port: Select your USB port
   - Upload Speed: `921600`
   - Flash Size: `4MB (FS:2MB OTA:~1019KB)`

4. **Upload the sketch**
   - Click the Upload button (→)
   - Wait for "Done uploading" message

---

## 🎮 Usage

### First Time Setup

1. **Power on the ESP8266**
   - Connect it to a USB power source

2. **Connect to WiFi AP**
   - The device creates a WiFi network named **"ZakatCalc-Setup"**
   - Connect to this network from your phone/computer

3. **Configure WiFi**
   - A captive portal should open automatically
   - If not, navigate to `http://192.168.4.1`
   - Select your home WiFi network and enter the password
   - Click Save

4. **Find the device IP**
   - Open Arduino IDE Serial Monitor (`Tools` → `Serial Monitor`)
   - Set baud rate to `115200`
   - The device will print its IP address after connecting to WiFi

5. **Access the calculator**
   - Open a browser and navigate to the IP address shown
   - Example: `http://192.168.1.100`

### Making It Publicly Accessible (Optional)

To access your ESP8266-hosted website from anywhere without port forwarding, you can use services like:
- **Cloudflare Tunnel** (Free)
- **Tailscale** (Free)
- **ngrok** (Free tier available)
- **PageKite** (Free trial)

These create secure tunnels to your device without requiring router configuration.

---

## 💻 Development

### Modifying the Interface

1. Edit `index.html` with your changes
2. Test locally by opening the file in a browser
3. Minify the HTML using a tool like [HTML Minifier](https://www.willpeavy.com/tools/minifier/)
4. Update the `zakat_html[]` constant in `ZakatCalc.ino`
5. Re-upload to ESP8266

### Project Structure

```
ZakatCalc/
├── ZakatCalc.ino       # Main Arduino sketch (ESP8266 code)
├── index.html          # Web interface (unminified, for development)
├── README.md           # This file
└── setup-photo.jpg     # Photo of the actual setup (coming soon)
```

---

## 🔧 Technical Details

### How It Works

1. **ESP8266** runs a lightweight web server using `ESPAsyncWebServer`
2. **WiFiManager** handles WiFi credentials without hardcoding
3. **LittleFS** file system stores any additional resources (if needed)
4. The entire HTML/CSS/JS interface is embedded in the Arduino sketch
5. All calculations happen **client-side** in JavaScript (no backend processing needed)

### Power Consumption

- **Active Mode**: ~80mA @ 3.3V (~0.26W)
- **Idle Mode**: ~15mA @ 3.3V (~0.05W)
- **Cost per year**: Less than $0.50 in electricity

### Network Requirements

- Any standard WiFi network (2.4GHz)
- No special router configuration needed for local access
- Optional tunnel service for public internet access

---

## 🎨 Features Breakdown

### Zakat Calculation
- Asset tracking (cash, gold, silver, investments, business, rental income)
- Liability deductions (debts)
- Real-time Nisab threshold calculation (85g gold equivalent)
- 2.5% Zakat calculation on zakatable wealth
- Visual indicators for eligibility

### User Interface
- **Responsive Design**: Works on phones, tablets, and desktops
- **Dark Mode**: Auto-detects system preference
- **Multi-language**: Switch between English, Arabic, Bengali, and Hindi
- **Print Support**: Generate printable Zakat reports
- **Real-time Updates**: Calculations update as you type

### Technical Features
- **No Database Required**: All calculations are client-side
- **Offline Capable**: Works without internet after initial load
- **Minimal Footprint**: Runs on 80KB RAM
- **Fast**: Sub-second response times

---

## 🌟 Why Self-Host on ESP8266?

### Cost Comparison

| Solution | Setup Cost | Monthly Cost | Annual Cost |
|----------|-----------|--------------|-------------|
| **ESP8266 (This Project)** | $6 | $0 | $0.50* |
| Shared Hosting | $0 | $5 | $60 |
| VPS | $0 | $10 | $120 |
| Cloud (AWS/Azure) | $0 | $15+ | $180+ |

*Only electricity costs

### Benefits
- 🌱 **Eco-Friendly**: Uses minimal power
- 🔒 **Privacy**: Your data stays in your home
- 🎓 **Educational**: Learn about IoT and embedded systems
- 🛠️ **Customizable**: Full control over hardware and software
- 📶 **Always On**: No service interruptions or shutdowns

### Limitations
- Limited to serving lightweight web pages
- Cannot handle high concurrent traffic (max ~10-20 users simultaneously)
- Slower processing than traditional servers
- Dependent on your home internet connection uptime

---

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Report bugs
- Suggest new features
- Improve documentation
- Submit pull requests

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

---

## 🙏 Acknowledgments

- Built with [Arduino](https://www.arduino.cc/)
- UI powered by [Tailwind CSS](https://tailwindcss.com/)
- Async web server by [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- WiFi management by [WiFiManager](https://github.com/tzapu/WiFiManager)

---

## 📞 Support

If you find this project helpful, please give it a ⭐ on GitHub!

For questions or issues, please [open an issue](https://github.com/sharf-shawon/ZakatCalc/issues).

---

## 🔮 Future Enhancements

- [ ] Add mDNS support for easy local access (e.g., `zakatchalc.local`)
- [ ] OTA (Over-The-Air) updates
- [ ] Data persistence using EEPROM/SPIFFS
- [ ] Historical Zakat tracking
- [ ] Multiple calculation methods (Maliki, Hanafi, etc.)
- [ ] Currency conversion support
- [ ] API integration for live gold/silver prices

---

<div align="center">

**Made with ❤️ and a $4 microcontroller**

Running 24/7 from my home since 2026

[GitHub](https://github.com/sharf-shawon/ZakatCalc) • [Issues](https://github.com/sharf-shawon/ZakatCalc/issues)

</div>
