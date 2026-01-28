#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

// WiFi credentials - Change these to your network!

const char* ssid = "xxxx";
const char* password = "xxxxxxxx";

// Create AsyncWebServer on port 80
AsyncWebServer server(80);

// Zakat Calculator HTML - Minified
// IMPORTANT: Replace the content between the quotes with your minified HTML
// ZAKAT_HTML_PLACEHOLDER
const char zakat_html[] PROGMEM = R"rawliteral(
<!doctypehtml><html lang="en"class="scroll-smooth"><meta charset="UTF-8"><meta name="viewport"content="width=device-width,initial-scale=1"><title>Zakat Calculator - Privacy Protected Islamic Zakat Nisab Calculation Tool | Powered By Wemos D1 Mini Pro</title><meta name="description"content="Free online Zakat calculator tool. Calculate your Islamic charitable obligation with accurate Nisab threshold, gold and silver prices. Support for multiple languages and currencies."><meta name="keywords"content="Zakat calculator, Islamic finance, Nisab threshold, Zakat obligation, Islamic charity, gold price, silver price, Islamic wealth management"><meta name="author"content="Sharfuddi Shawon"><meta name="robots"content="index, follow"><meta name="language"content="English"><meta name="revisit-after"content="7 days"><meta name="theme-color"content="#22c55e"><meta property="og:title"content="Zakat Calculator - Calculate Your Islamic Charitable Obligation"><meta property="og:description"content="Free Zakat calculator with support for multiple languages. Calculate based on cash, gold, silver, investments and more."><meta property="og:type"content="website"><meta property="og:url"content="https://zakat.dhakaiya.dev"><meta property="og:site_name"content="Zakat Calculator"><meta property="og:locale"content="en_US"><meta property="og:locale:alternate"content="ar_SA"><meta property="og:locale:alternate"content="bn_BD"><meta property="og:locale:alternate"content="hi_IN"><meta name="twitter:card"content="summary_large_image"><meta name="twitter:title"content="Zakat Calculator - Islamic Finance Tool"><meta name="twitter:description"content="Free online Zakat calculator. Calculate your Zakat obligation based on gold, silver, cash and investments."><script type="application/ld+json">{
      "@context": "https://schema.org",
      "@type": "WebApplication",
      "name": "Zakat Calculator - Privacy Protected Islamic Zakat Nisab Calculation Tool",
      "description": "Free online privacy protected Zakat calculator tool for calculating Islamic zakat obligations. Your information never leaves your device.",
      "url": "https://zakat.dhakaiya.dev",
      "applicationCategory": "ProductivityApplication",
      "offers": {
        "@type": "Offer",
        "price": "0",
        "priceCurrency": "USD"
      },
      "creator": {
        "@type": "Person",
        "name": "Sharfuddin Shawon",
        "url": "https://github.com/sharf-shawon"
      },
      "inLanguage": ["en", "ar", "bn", "hi"],
      "operatingSystem": "Web",
      "featureList": [
        "Multi-language support",
        "Real-time Zakat calculation",
        "Zakat Nisab threshold calculation",
        "Privacy protected; runs entirely in browser.",
        "Works on all devices"
      ]
    }</script><link rel="canonical"href="https://zakat.dhakaiya.dev"><link rel="icon"type="image/svg+xml"href="data:image/svg+xml,<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 100 100'><text y='.9em' font-size='90'>🕌</text></svg>"><script src="https://cdn.tailwindcss.com"></script><script>tailwind.config={darkMode:"class",theme:{extend:{colors:{primary:{50:"#f0fdf4",100:"#dcfce7",200:"#bbf7d0",300:"#86efac",400:"#4ade80",500:"#22c55e",600:"#16a34a",700:"#15803d",800:"#166534",900:"#145231"}}}}}</script><style>@media (prefers-color-scheme:dark){html{color-scheme:dark}}@media (prefers-color-scheme:light){html{color-scheme:light}}html{transition:background-color .3s,color .3s}::-webkit-scrollbar{width:8px}::-webkit-scrollbar-track{background:0 0}::-webkit-scrollbar-thumb{background:#22c55e;border-radius:4px}::-webkit-scrollbar-thumb:hover{background:#16a34a}@keyframes slideIn{from{opacity:0;transform:translateY(10px)}to{opacity:1;transform:translateY(0)}}.animate-slide-in{animation:slideIn .3s ease-out}.glass{background:rgba(255,255,255,.7);backdrop-filter:blur(10px);border:1px solid rgba(255,255,255,.2)}.dark .glass{background:rgba(15,23,42,.7);border:1px solid rgba(148,163,184,.1)}input:focus-visible{outline:0}button{position:relative;overflow:hidden}button::after{content:'';position:absolute;top:50%;left:50%;width:0;height:0;border-radius:50%;background:rgba(255,255,255,.3);transform:translate(-50%,-50%);transition:width .6s,height .6s}button:active::after{width:300px;height:300px}</style><body class="bg-gray-50 dark:bg-slate-900 text-slate-900 dark:text-slate-100 transition-colors duration-300"><div class="sticky top-0 z-50 bg-white dark:bg-slate-800 shadow-md border-b border-gray-200 dark:border-slate-700 transition-colors duration-300"><div class="max-w-5xl mx-auto px-4 py-4 flex justify-between items-center"><div class="flex items-center gap-3"><div class="text-2xl">🕌</div><h1 class="text-2xl font-bold text-primary-600 dark:text-primary-400">Zakat Calculator</h1></div><div class="flex items-center gap-3"><div class="relative group"><button class="px-4 py-2 rounded-lg bg-gray-100 dark:bg-slate-700 hover:bg-gray-200 dark:hover:bg-slate-600 transition-colors duration-200 text-sm font-medium flex items-center gap-2"><span id="langDisplay">🇺🇸 English</span> <svg class="w-4 h-4"fill="none"stroke="currentColor"viewBox="0 0 24 24"><path stroke-linecap="round"stroke-linejoin="round"stroke-width="2"d="M19 14l-7 7m0 0l-7-7m7 7V3"/></svg></button><div class="absolute right-0 mt-2 w-48 bg-white dark:bg-slate-700 rounded-lg shadow-xl opacity-0 invisible group-hover:opacity-100 group-hover:visible transition-all duration-200"><button onclick='setLanguage("en")'class="w-full text-left px-4 py-3 hover:bg-gray-100 dark:hover:bg-slate-600 rounded-t-lg transition-colors duration-200">🇺🇸 English</button> <button onclick='setLanguage("ar")'class="w-full text-left px-4 py-3 hover:bg-gray-100 dark:hover:bg-slate-600 transition-colors duration-200">🇸🇦 العربية</button> <button onclick='setLanguage("bn")'class="w-full text-left px-4 py-3 hover:bg-gray-100 dark:hover:bg-slate-600 transition-colors duration-200">🇧🇩 বাংলা</button> <button onclick='setLanguage("hi")'class="w-full text-left px-4 py-3 hover:bg-gray-100 dark:hover:bg-slate-600 rounded-b-lg transition-colors duration-200">🇮🇳 हिंदी</button></div></div><button onclick="toggleDarkMode()"class="p-2 rounded-lg bg-gray-100 dark:bg-slate-700 hover:bg-gray-200 dark:hover:bg-slate-600 transition-colors duration-200"title="Toggle dark mode"><svg id="sunIcon"class="w-5 h-5 text-yellow-500 hidden"fill="currentColor"viewBox="0 0 20 20"><path fill-rule="evenodd"d="M10 2a1 1 0 011 1v2a1 1 0 11-2 0V3a1 1 0 011-1zm4 8a4 4 0 11-8 0 4 4 0 018 0zm-.464 4.95l-2.12-2.12a1 1 0 00-1.414 0l-.707.707a1 1 0 001.414 1.414l.707-.707 2.12 2.12a1 1 0 001.414-1.414l-.707-.707z"clip-rule="evenodd"/></svg> <svg id="moonIcon"class="w-5 h-5 text-blue-400"fill="currentColor"viewBox="0 0 20 20"><path d="M17.293 13.293A8 8 0 016.707 2.707a8.001 8.001 0 1010.586 10.586z"/></svg></button></div></div></div><div class="max-w-5xl mx-auto px-4 py-8"><div class="mb-8 bg-gradient-to-r from-primary-50 to-emerald-50 dark:from-slate-800 dark:to-slate-700 rounded-xl p-6 border border-primary-200 dark:border-slate-600"><p class="text-center text-slate-700 dark:text-slate-300"id="subtitle">Calculate your Zakat obligation with complete breakdown</div><div class="grid grid-cols-1 lg:grid-cols-3 gap-6 mb-8"><div class="lg:col-span-1 bg-white dark:bg-slate-800 rounded-xl shadow-lg p-6 border border-gray-200 dark:border-slate-700"><h2 class="text-xl font-bold mb-6 flex items-center gap-2 text-slate-900 dark:text-white"><span>💰</span> <span id="pricesTitle">Metal Prices</span></h2><div class="space-y-4"><div><label id="goldPriceLabel"class="block text-sm font-medium mb-2 text-slate-700 dark:text-slate-300">Gold Price (per gram)</label><div class="flex items-center gap-2"><input type="number"id="goldPrice"value="78.50"step="0.01"class="flex-1 px-4 py-2 rounded-lg border border-gray-300 dark:border-slate-600 bg-white dark:bg-slate-700 text-slate-900 dark:text-white focus:ring-2 focus:ring-primary-500 focus:border-transparent transition-all duration-200"oninput="calculate()"> <span class="text-slate-600 dark:text-slate-400 font-medium">$</span></div></div><div><label id="silverPriceLabel"class="block text-sm font-medium mb-2 text-slate-700 dark:text-slate-300">Silver Price (per gram)</label><div class="flex items-center gap-2"><input type="number"id="silverPrice"value="0.95"step="0.01"class="flex-1 px-4 py-2 rounded-lg border border-gray-300 dark:border-slate-600 bg-white dark:bg-slate-700 text-slate-900 dark:text-white focus:ring-2 focus:ring-primary-500 focus:border-transparent transition-all duration-200"oninput="calculate()"> <span class="text-slate-600 dark:text-slate-400 font-medium">$</span></div></div><div class="p-4 bg-blue-50 dark:bg-slate-700 rounded-lg text-sm text-blue-800 dark:text-blue-300"><p id="priceHint">💡 Prices update automatically. Adjust for current market rates.</div></div></div><div class="lg:col-span-2 bg-white dark:bg-slate-800 rounded-xl shadow-lg p-6 border border-gray-200 dark:border-slate-700"><h2 class="text-xl font-bold mb-6 flex items-center gap-2 text-slate-900 dark:text-white"><span>💎</span> <span id="assetsTitle">Assets & Investments</span></h2><div class="grid grid-cols-1 md:grid-cols-2 gap-4"><div><label id="cashLabel"class="block text-sm font-medium mb-2 text-slate-700 dark:text-slate-300">Cash & Bank Balances</label> <input type="number"id="cash"placeholder="0.00"oninput="calculate()"class="w-full px-4 py-2 rounded-lg border border-gray-300 dark:border-slate-600 bg-white dark:bg-slate-700 text-slate-900 dark:text-white focus:ring-2 focus:ring-primary-500 focus:border-transparent transition-all duration-200"></div><div><label id="goldLabel"class="block text-sm font-medium mb-2 text-slate-700 dark:text-slate-300">Gold (grams)</label> <input type="number"id="gold"placeholder="0"oninput="calculate()"class="w-full px-4 py-2 rounded-lg border border-gray-300 dark:border-slate-600 bg-white dark:bg-slate-700 text-slate-900 dark:text-white focus:ring-2 focus:ring-primary-500 focus:border-transparent transition-all duration-200"></div><div><label id="silverLabel"class="block text-sm font-medium mb-2 text-slate-700 dark:text-slate-300">Silver (grams)</label> <input type="number"id="silver"placeholder="0"oninput="calculate()"class="w-full px-4 py-2 rounded-lg border border-gray-300 dark:border-slate-600 bg-white dark:bg-slate-700 text-slate-900 dark:text-white focus:ring-2 focus:ring-primary-500 focus:border-transparent transition-all duration-200"></div><div><label id="investmentsLabel"class="block text-sm font-medium mb-2 text-slate-700 dark:text-slate-300">Stocks/Investments</label> <input type="number"id="investments"placeholder="0.00"oninput="calculate()"class="w-full px-4 py-2 rounded-lg border border-gray-300 dark:border-slate-600 bg-white dark:bg-slate-700 text-slate-900 dark:text-white focus:ring-2 focus:ring-primary-500 focus:border-transparent transition-all duration-200"></div><div><label id="businessLabel"class="block text-sm font-medium mb-2 text-slate-700 dark:text-slate-300">Business Inventory</label> <input type="number"id="business"placeholder="0.00"oninput="calculate()"class="w-full px-4 py-2 rounded-lg border border-gray-300 dark:border-slate-600 bg-white dark:bg-slate-700 text-slate-900 dark:text-white focus:ring-2 focus:ring-primary-500 focus:border-transparent transition-all duration-200"></div><div><label id="rentalLabel"class="block text-sm font-medium mb-2 text-slate-700 dark:text-slate-300">Rental Income (Annual)</label> <input type="number"id="rental"placeholder="0.00"oninput="calculate()"class="w-full px-4 py-2 rounded-lg border border-gray-300 dark:border-slate-600 bg-white dark:bg-slate-700 text-slate-900 dark:text-white focus:ring-2 focus:ring-primary-500 focus:border-transparent transition-all duration-200"></div></div></div></div><div class="bg-white dark:bg-slate-800 rounded-xl shadow-lg p-6 border border-gray-200 dark:border-slate-700 mb-8"><h2 class="text-xl font-bold mb-6 flex items-center gap-2 text-slate-900 dark:text-white"><span>📉</span> <span id="liabilitiesTitle">Liabilities (Deductible)</span></h2><div class="grid grid-cols-1 md:grid-cols-3 gap-4"><div><label id="debtsLabel"class="block text-sm font-medium mb-2 text-slate-700 dark:text-slate-300">Debts & Loans</label> <input type="number"id="debts"placeholder="0.00"oninput="calculate()"class="w-full px-4 py-2 rounded-lg border border-gray-300 dark:border-slate-600 bg-white dark:bg-slate-700 text-slate-900 dark:text-white focus:ring-2 focus:ring-primary-500 focus:border-transparent transition-all duration-200"></div></div></div><div class="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-4 gap-6 mb-8"id="resultsCards"><div class="bg-gradient-to-br from-blue-500 to-blue-600 text-white rounded-xl shadow-lg p-6 transform hover:scale-105 transition-transform duration-300 animate-slide-in"><p class="text-sm font-medium opacity-90 mb-2"id="totalWealthTitle">Total Wealth<p class="text-3xl font-bold mb-2"id="totalWealth">$0.00<p class="text-xs opacity-75">All assets combined</div><div class="bg-gradient-to-br from-orange-500 to-orange-600 text-white rounded-xl shadow-lg p-6 transform hover:scale-105 transition-transform duration-300 animate-slide-in"><p class="text-sm font-medium opacity-90 mb-2"id="deductibleTitle">Deductible<p class="text-3xl font-bold mb-2"id="totalDeductible">$0.00<p class="text-xs opacity-75">Liabilities only</div><div class="bg-gradient-to-br from-emerald-500 to-emerald-600 text-white rounded-xl shadow-lg p-6 transform hover:scale-105 transition-transform duration-300 animate-slide-in"><p class="text-sm font-medium opacity-90 mb-2"id="zakatableTitle">Zakatable Wealth<p class="text-3xl font-bold mb-2"id="zakatableWealth">$0.00<p class="text-xs opacity-75">Net wealth</div><div class="bg-gradient-to-br from-purple-500 to-purple-600 text-white rounded-xl shadow-lg p-6 transform hover:scale-105 transition-transform duration-300 animate-slide-in"><p class="text-sm font-medium opacity-90 mb-2"id="nisabTitle">Nisab Threshold<p class="text-3xl font-bold mb-2"id="nisabAmount">$0.00<p class="text-xs opacity-75">85g gold equivalent</div></div><div class="bg-gradient-to-r from-primary-500 to-emerald-500 text-white rounded-xl shadow-2xl p-8 mb-8 transform hover:shadow-xl transition-all duration-300 animate-slide-in"><div class="text-center"><p class="text-lg font-semibold opacity-90 mb-2"id="payableTitle">Payable Zakat (2.5%)<p class="text-6xl font-black mb-4"id="payableZakat">$0.00<p class="text-sm opacity-90"id="nisabStatus">Calculate above to see your Zakat amount</div></div><div id="nisabStatusBox"class="bg-yellow-50 dark:bg-slate-700 border-l-4 border-yellow-400 p-4 rounded-lg mb-8 hidden"><p class="text-yellow-800 dark:text-yellow-200"id="nisabStatusMessage">Your wealth is below the Nisab threshold. No Zakat is due at this time.</div><div class="flex flex-col sm:flex-row gap-4 justify-center"><button onclick="calculate()"class="px-8 py-3 bg-primary-500 hover:bg-primary-600 text-white font-bold rounded-lg shadow-lg transition-all duration-200 flex items-center justify-center gap-2"><span>🔄</span> <span id="calculateBtn">Calculate Zakat</span></button> <button onclick="resetForm()"class="px-8 py-3 bg-gray-400 dark:bg-slate-600 hover:bg-gray-500 dark:hover:bg-slate-500 text-white font-bold rounded-lg shadow-lg transition-all duration-200 flex items-center justify-center gap-2"><span>🔁</span> <span id="resetBtn">Reset All</span></button> <button onclick="printZakat()"class="px-8 py-3 bg-blue-500 hover:bg-blue-600 text-white font-bold rounded-lg shadow-lg transition-all duration-200 flex items-center justify-center gap-2"><span>🖨️</span> <span id="printBtn">Print Report</span></button></div></div><footer class="bg-gray-100 dark:bg-slate-800 border-t border-gray-200 dark:border-slate-700 mt-12 py-6 transition-colors duration-300"><div class="max-w-5xl mx-auto px-4 text-center text-slate-600 dark:text-slate-400 text-sm"><p id="footer">© 2026 Zakat Calculator | Running on ESP8266 | <a href="https://github.com/sharf-shawon/ZakatCalc"target="_blank"rel="noopener noreferrer">GitHub</a></div></footer><script>let translations={en:{subtitle:"Calculate your Zakat obligation with complete breakdown",pricesTitle:"Metal Prices",goldPriceLabel:"Gold Price (per gram)",silverPriceLabel:"Silver Price (per gram)",priceHint:"💡 Prices update automatically. Adjust for current market rates.",assetsTitle:"Assets & Investments",cashLabel:"Cash & Bank Balances",goldLabel:"Gold (grams)",silverLabel:"Silver (grams)",investmentsLabel:"Stocks/Investments",businessLabel:"Business Inventory",rentalLabel:"Rental Income (Annual)",liabilitiesTitle:"Liabilities (Deductible)",debtsLabel:"Debts & Loans",totalWealthTitle:"Total Wealth",deductibleTitle:"Deductible",zakatableTitle:"Zakatable Wealth",nisabTitle:"Nisab Threshold",payableTitle:"Payable Zakat (2.5%)",nisabStatus:"Calculate above to see your Zakat amount",calculateBtn:"Calculate Zakat",resetBtn:"Reset All",printBtn:"Print Report",footer:"© 2026 Zakat Calculator | Running on ESP8266",belowNisab:"Your wealth is below the Nisab threshold. No Zakat is due at this time.",aboveNisab:"✅ Your wealth exceeds the Nisab. Zakat is due.",langDisplay:"🇺🇸 English"},ar:{subtitle:"احسب التزامك بالزكاة مع تفصيل كامل",pricesTitle:"أسعار المعادن",goldPriceLabel:"سعر الذهب (لكل جرام)",silverPriceLabel:"سعر الفضة (لكل جرام)",priceHint:"💡 تحديث الأسعار تلقائياً. عدّل حسب أسعار السوق الحالية.",assetsTitle:"الأصول والاستثمارات",cashLabel:"النقود والرصيد البنكي",goldLabel:"الذهب (جرام)",silverLabel:"الفضة (جرام)",investmentsLabel:"الأسهم والاستثمارات",businessLabel:"مخزون البضائع",rentalLabel:"دخل الإيجار (سنوي)",liabilitiesTitle:"الالتزامات (مقابلة)",debtsLabel:"الديون والقروض",totalWealthTitle:"إجمالي الثروة",deductibleTitle:"مقابل",zakatableTitle:"المال الزكوي",nisabTitle:"حد النصاب",payableTitle:"الزكاة المستحقة (٢.٥٪)",nisabStatus:"احسب أعلاه لترى مبلغ الزكاة",calculateBtn:"احسب الزكاة",resetBtn:"إعادة تعيين الكل",printBtn:"طباعة التقرير",footer:"© 2026 Zakat Calculator | Running on ESP8266",belowNisab:"ثروتك أقل من حد النصاب. لا زكاة مستحقة في الوقت الحالي.",aboveNisab:"✅ ثروتك تتجاوز حد النصاب. الزكاة مستحقة.",langDisplay:"🇸🇦 العربية"},bn:{subtitle:"সম্পূর্ণ বিস্তারিত সহ আপনার জাকাত দায়িত্ব গণনা করুন",pricesTitle:"ধাতুর দাম",goldPriceLabel:"সোনার দাম (প্রতি গ্রাম)",silverPriceLabel:"রুপার দাম (প্রতি গ্রাম)",priceHint:"💡 দাম স্বয়ংক্রিয়ভাবে আপডেট হয়। বর্তমান বাজার দরের জন্য সামঞ্জস্য করুন।",assetsTitle:"সম্পদ ও বিনিয়োগ",cashLabel:"নগদ ও ব্যাঙ্ক ব্যালেন্স",goldLabel:"সোনা (গ্রাম)",silverLabel:"রুপা (গ্রাম)",investmentsLabel:"শেয়ার/বিনিয়োগ",businessLabel:"ব্যবসার মজুদ",rentalLabel:"ভাড়া আয় (বার্ষিক)",liabilitiesTitle:"দায় (ঘুচনযোগ্য)",debtsLabel:"ঋণ ও লোন",totalWealthTitle:"মোট সম্পদ",deductibleTitle:"ঘুচনযোগ্য",zakatableTitle:"জাকাতযোগ্য সম্পদ",nisabTitle:"নিসাব সীমা",payableTitle:"পরিশোধ্য জাকাত (২.৫%)",nisabStatus:"আপনার জাকাত পরিমাণ দেখতে উপরে গণনা করুন",calculateBtn:"জাকাত গণনা করুন",resetBtn:"সব রিসেট করুন",printBtn:"রিপোর্ট প্রিন্ট করুন",footer:"© 2026 Zakat Calculator | Running on ESP8266",belowNisab:"আপনার সম্পদ নিসাব সীমার নিচে। এই সময়ে কোনো জাকাত পরিশোধ্য নয়।",aboveNisab:"✅ আপনার সম্পদ নিসাব সীমা অতিক্রম করে। জাকাত পরিশোধ্য।",langDisplay:"🇧🇩 বাংলা"},hi:{subtitle:"पूर्ण विश्लेषण के साथ अपनी जकात देयता की गणना करें",pricesTitle:"धातु की कीमतें",goldPriceLabel:"सोने की कीमत (प्रति ग्राम)",silverPriceLabel:"चांदी की कीमत (प्रति ग्राम)",priceHint:"💡 कीमतें स्वचालित रूप से अपडेट होती हैं। वर्तमान बाजार दरों के अनुसार समायोजित करें।",assetsTitle:"संपत्ति और निवेश",cashLabel:"नकद और बैंक बैलेंस",goldLabel:"सोना (ग्राम)",silverLabel:"चांदी (ग्राम)",investmentsLabel:"शेयर/निवेश",businessLabel:"व्यवसाय का माल",rentalLabel:"किराया आय (वार्षिक)",liabilitiesTitle:"दायित्व (काटने योग्य)",debtsLabel:"ऋण और लोन",totalWealthTitle:"कुल संपत्ति",deductibleTitle:"काटने योग्य",zakatableTitle:"जकात योग्य संपत्ति",nisabTitle:"निसाब सीमा",payableTitle:"देय जकात (2.5%)",nisabStatus:"अपनी जकात राशि देखने के लिए ऊपर गणना करें",calculateBtn:"जकात की गणना करें",resetBtn:"सभी रीसेट करें",printBtn:"रिपोर्ट प्रिंट करें",footer:"© 2026 Zakat Calculator | Running on ESP8266",belowNisab:"आपकी संपत्ति निसाब सीमा से नीचे है। इस समय कोई जकात देय नहीं है।",aboveNisab:"✅ आपकी संपत्ति निसाब सीमा से अधिक है। जकात देय है।",langDisplay:"🇮🇳 हिंदी"}},currentLang="en",isDarkMode=!1;function initializeDarkMode(){window.matchMedia&&window.matchMedia("(prefers-color-scheme: dark)").matches?(isDarkMode=!0,document.documentElement.classList.add("dark")):(isDarkMode=!1,document.documentElement.classList.remove("dark")),updateDarkModeIcons(),window.matchMedia("(prefers-color-scheme: dark)").addEventListener("change",e=>{(e.matches?enableDarkMode:disableDarkMode)()})}function toggleDarkMode(){(isDarkMode?disableDarkMode:enableDarkMode)()}function enableDarkMode(){isDarkMode=!0,document.documentElement.classList.add("dark"),localStorage.setItem("theme","dark"),updateDarkModeIcons()}function disableDarkMode(){isDarkMode=!1,document.documentElement.classList.remove("dark"),localStorage.setItem("theme","light"),updateDarkModeIcons()}function updateDarkModeIcons(){var e=document.getElementById("sunIcon"),t=document.getElementById("moonIcon");isDarkMode?(e.classList.remove("hidden"),t.classList.add("hidden")):(e.classList.add("hidden"),t.classList.remove("hidden"))}function setLanguage(e){currentLang=e,localStorage.setItem("language",e);var t=translations[e];document.getElementById("subtitle").textContent=t.subtitle,document.getElementById("pricesTitle").textContent=t.pricesTitle,document.getElementById("goldPriceLabel").textContent=t.goldPriceLabel,document.getElementById("silverPriceLabel").textContent=t.silverPriceLabel,document.getElementById("priceHint").textContent=t.priceHint,document.getElementById("assetsTitle").textContent=t.assetsTitle,document.getElementById("cashLabel").textContent=t.cashLabel,document.getElementById("goldLabel").textContent=t.goldLabel,document.getElementById("silverLabel").textContent=t.silverLabel,document.getElementById("investmentsLabel").textContent=t.investmentsLabel,document.getElementById("businessLabel").textContent=t.businessLabel,document.getElementById("rentalLabel").textContent=t.rentalLabel,document.getElementById("liabilitiesTitle").textContent=t.liabilitiesTitle,document.getElementById("debtsLabel").textContent=t.debtsLabel,document.getElementById("totalWealthTitle").textContent=t.totalWealthTitle,document.getElementById("deductibleTitle").textContent=t.deductibleTitle,document.getElementById("zakatableTitle").textContent=t.zakatableTitle,document.getElementById("nisabTitle").textContent=t.nisabTitle,document.getElementById("payableTitle").textContent=t.payableTitle,document.getElementById("nisabStatus").textContent=t.nisabStatus,document.getElementById("calculateBtn").textContent=t.calculateBtn,document.getElementById("resetBtn").textContent=t.resetBtn,document.getElementById("printBtn").textContent=t.printBtn,document.getElementById("footer").textContent=t.footer,document.getElementById("langDisplay").textContent=t.langDisplay,document.documentElement.dir="ar"===e?"rtl":"ltr",document.documentElement.lang=e,calculate()}function calculate(){var e=parseFloat(document.getElementById("goldPrice").value)||78.5,t=parseFloat(document.getElementById("silverPrice").value)||.95,a=parseFloat(document.getElementById("cash").value)||0,l=parseFloat(document.getElementById("gold").value)||0,n=parseFloat(document.getElementById("silver").value)||0,i=parseFloat(document.getElementById("investments").value)||0,o=parseFloat(document.getElementById("business").value)||0,s=parseFloat(document.getElementById("rental").value)||0,d=parseFloat(document.getElementById("debts").value)||0,a=a+l*e+n*t+i+o+.025*s,l=Math.max(0,a-d),n=85*e,t=n<=l,i=t?.025*l:0,o=e=>e.toLocaleString((currentLang,"en-US"),{minimumFractionDigits:0,maximumFractionDigits:2}),s=(document.getElementById("totalWealth").textContent="$"+o(a),document.getElementById("totalDeductible").textContent="$"+o(d),document.getElementById("zakatableWealth").textContent="$"+o(l),document.getElementById("nisabAmount").textContent="$"+o(n),document.getElementById("payableZakat").textContent="$"+o(i),translations[currentLang]),e=document.getElementById("nisabStatusBox"),d=document.getElementById("nisabStatusMessage");t&&0<a?(e.classList.add("hidden"),document.getElementById("nisabStatus").textContent=s.aboveNisab):(d.textContent=s.belowNisab,e.classList.remove("hidden"),document.getElementById("nisabStatus").textContent=s.belowNisab)}function resetForm(){document.querySelectorAll('input[type="number"]').forEach(e=>{"goldPrice"===e.id?e.value="78.50":"silverPrice"===e.id?e.value="0.95":e.value=""}),calculate()}function printZakat(){window.print()}document.addEventListener("DOMContentLoaded",function(){var e=localStorage.getItem("theme"),e=(("dark"===e?enableDarkMode:"light"===e?disableDarkMode:initializeDarkMode)(),localStorage.getItem("language")||"en");setLanguage(e),document.querySelectorAll('input[type="number"]').forEach(e=>{e.addEventListener("input",calculate)}),calculate()}),window.calculate=calculate,window.resetForm=resetForm,window.printZakat=printZakat,window.setLanguage=setLanguage,window.toggleDarkMode=toggleDarkMode</script>
)rawliteral";


// ========================================
// HELPER FUNCTION - PRINT WiFi STATUS
// ========================================
void printWiFiStatus() {
    Serial.println("\n╔════════════════════════════════════╗");
    Serial.println("║   WiFi Connection Details          ║");
    Serial.println("╚════════════════════════════════════╝");
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Gateway: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("Subnet Mask: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("Signal Strength (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
    Serial.println();
}

// ========================================
// SETUP FUNCTION
// ========================================
void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("\n\n");
    Serial.println("╔════════════════════════════════════╗");
    Serial.println("║   Zakat Calculator - ESP8266       ║");
    Serial.println("║   Starting initialization...        ║");
    Serial.println("╚════════════════════════════════════╝");
    
    // Initialize LittleFS
    if (!LittleFS.begin()) {
        Serial.println("[ERROR] Failed to mount LittleFS");
        delay(1000);
        ESP.restart();
    }
    Serial.println("[✓] LittleFS mounted successfully");
    
    // Connect to WiFi
    Serial.println("[*] Connecting to WiFi...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    // Wait for connection with timeout
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 30) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    Serial.println();
    
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("[ERROR] Failed to connect to WiFi");
        Serial.println("[ERROR] Please check your SSID and password");
        delay(3000);
        ESP.restart();
    }
    
    Serial.println("[✓] WiFi connected successfully!");
    Serial.print("[✓] IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("[✓] SSID: ");
    Serial.println(WiFi.SSID());
    
    // Print WiFi connection details
    printWiFiStatus();
    
    // ========================================
    // SETUP ASYNC WEB SERVER ROUTES
    // ========================================
    
    // Root route - serve HTML
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("[GET] / - Serving Zakat Calculator HTML");
        request->send_P(200, "text/html", zakat_html);
    });
    
    // Catch-all for CSS, JS, etc (if needed)
    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(204); // No content
    });
    
    // Health check endpoint (useful for Cloudflare monitoring)
    server.on("/health", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("[GET] /health - Health check");
        request->send(200, "application/json", "{\"status\":\"ok\",\"uptime\":" + String(millis()/1000) + "}");
    });
    
    // Device info endpoint
    server.on("/api/info", HTTP_GET, [](AsyncWebServerRequest *request){
        String json = "{";
        json += "\"device\":\"ESP8266\",";
        json += "\"ip\":\"" + WiFi.localIP().toString() + "\",";
        json += "\"ssid\":\"" + WiFi.SSID() + "\",";
        json += "\"rssi\":" + String(WiFi.RSSI()) + ",";
        json += "\"heap\":" + String(ESP.getFreeHeap()) + ",";
        json += "\"uptime\":" + String(millis()/1000) + ",";
        json += "\"version\":\"1.0.0\"";
        json += "}";
        request->send(200, "application/json", json);
    });
    
    // WiFi reset endpoint
    server.on("/api/wifi/reset", HTTP_POST, [](AsyncWebServerRequest *request){
        Serial.println("[POST] /api/wifi/reset - Restarting device");
        request->send(200, "application/json", "{\"status\":\"restarting\"}");
        delay(1000);
        ESP.restart();
    });
    
    // Default handler for undefined routes
    server.onNotFound([](AsyncWebServerRequest *request){
        Serial.print("[GET] ");
        Serial.print(request->url());
        Serial.println(" - NOT FOUND - Redirecting to root");
        request->redirect("/");
    });
    
    // Start the server
    server.begin();
    
    Serial.println("\n╔════════════════════════════════════╗");
    Serial.println("║   Server Started Successfully!      ║");
    Serial.print("║   Access: http://");
    Serial.print(WiFi.localIP());
    Serial.println("        ║");
    Serial.println("╚════════════════════════════════════╝\n");
}

// ========================================
// LOOP FUNCTION
// ========================================
void loop() {
    // AsyncWebServer handles everything automatically
    // No need for anything here - it's event-driven
    
    // Optional: Print status every 30 seconds
    static unsigned long lastCheck = 0;
    if (millis() - lastCheck > 30000) {
        lastCheck = millis();
        
        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("[!] WiFi disconnected! Attempting reconnection...");
            WiFi.reconnect();
        } else {
            Serial.print("[Status] IP: ");
            Serial.print(WiFi.localIP());
            Serial.print(" | RSSI: ");
            Serial.print(WiFi.RSSI());
            Serial.print(" dBm | Heap: ");
            Serial.print(ESP.getFreeHeap());
            Serial.println(" bytes");
        }
    }
    
    delay(100); // Small delay to prevent watchdog timeout
}
