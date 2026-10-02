#include <iostream>
#include <string>
#include <regex>
#include <cstdio>
#include <array>

std::string fetchPage(const std::string& url) {
#ifdef _WIN32
    std::string command = "curl.exe -L --max-time 20 -A \"CognifyzEducationalScraper/1.0\" \"" + url + "\" 2>nul";
    FILE* pipe = _popen(command.c_str(), "r");
#else
    std::string command = "curl -L --max-time 20 -A \"CognifyzEducationalScraper/1.0\" \"" + url + "\" 2>/dev/null";
    FILE* pipe = popen(command.c_str(), "r");
#endif

    if (!pipe) return "";

    std::array<char, 4096> buffer{};
    std::string result;
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe) != nullptr) {
        result += buffer.data();
    }

#ifdef _WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif
    return result;
}

std::string stripTags(const std::string& html) {
    std::string text = std::regex_replace(html, std::regex("<[^>]*>"), "");
    text = std::regex_replace(text, std::regex("\\s+"), " ");
    return text;
}

int main() {
    std::cout << "=== Interactive Web Scraper ===\n";
    std::cout << "Enter a public http/https URL: ";

    std::string url;
    std::getline(std::cin, url);

    if (url.rfind("http://", 0) != 0 && url.rfind("https://", 0) != 0) {
        std::cout << "Invalid URL. Use http:// or https://\n";
        return 0;
    }

    std::string html = fetchPage(url);
    if (html.empty()) {
        std::cout << "Request failed or returned no content.\n";
        return 0;
    }

    std::smatch match;
    std::regex titleRegex("<title[^>]*>([\\s\\S]*?)</title>", std::regex::icase);
    if (std::regex_search(html, match, titleRegex)) {
        std::cout << "\nTitle:\n" << stripTags(match[1].str()) << "\n";
    } else {
        std::cout << "\nTitle:\nNo title found.\n";
    }

    std::cout << "\nHeadings:\n";
    std::regex headingRegex("<h[1-3][^>]*>([\\s\\S]*?)</h[1-3]>", std::regex::icase);
    auto headingBegin = std::sregex_iterator(html.begin(), html.end(), headingRegex);
    auto headingEnd = std::sregex_iterator();

    int count = 0;
    for (auto it = headingBegin; it != headingEnd && count < 20; ++it) {
        std::string heading = stripTags((*it)[1].str());
        if (!heading.empty()) std::cout << (++count) << ". " << heading << "\n";
    }
    if (count == 0) std::cout << "No headings found.\n";

    std::cout << "\nLinks:\n";
    std::regex linkRegex("<a[^>]*href=[\"']([^\"']+)[\"'][^>]*>([\\s\\S]*?)</a>", std::regex::icase);
    auto linkBegin = std::sregex_iterator(html.begin(), html.end(), linkRegex);
    auto linkEnd = std::sregex_iterator();

    count = 0;
    for (auto it = linkBegin; it != linkEnd && count < 20; ++it) {
        std::string href = (*it)[1].str();
        std::string textValue = stripTags((*it)[2].str());
        if (!textValue.empty()) {
            std::cout << (++count) << ". " << textValue << " -> " << href << "\n";
        }
    }
    if (count == 0) std::cout << "No links found.\n";

    return 0;
}
