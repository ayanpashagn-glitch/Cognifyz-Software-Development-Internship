#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <cstdlib>
#include <cstdio>

using namespace std;

string fetchPage(const string& url) {
    const string fileName = "page.html";

    string command =
        "curl.exe -L --max-time 20 "
        "-A \"CognifyzEducationalScraper/1.0\" "
        "-o \"" + fileName + "\" \"" + url + "\"";

    int result = system(command.c_str());

    if (result != 0) {
        return "";
    }

    ifstream file(fileName, ios::in | ios::binary);

    if (!file.is_open()) {
        return "";
    }

    string html(
        (istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>()
    );

    file.close();
    remove(fileName.c_str());

    return html;
}

string stripTags(const string& html) {
    string text = regex_replace(
        html,
        regex("<[^>]*>"),
        ""
    );

    text = regex_replace(
        text,
        regex("\\s+"),
        " "
    );

    return text;
}

int main() {
    cout << "=== Interactive Web Scraper ===\n";
    cout << "Enter a public http/https URL: ";

    string url;
    getline(cin, url);

    if (
        url.rfind("http://", 0) != 0 &&
        url.rfind("https://", 0) != 0
    ) {
        cout << "Invalid URL. Use http:// or https://\n";
        return 0;
    }

    cout << "\nFetching website...\n";

    string html = fetchPage(url);

    if (html.empty()) {
        cout << "Request failed or returned no content.\n";
        return 0;
    }

    smatch match;

    regex titleRegex(
        "<title[^>]*>([\\s\\S]*?)</title>",
        regex::icase
    );

    cout << "\nTitle:\n";

    if (regex_search(html, match, titleRegex)) {
        cout << stripTags(match[1].str()) << "\n";
    } else {
        cout << "No title found.\n";
    }

    cout << "\nHeadings:\n";

    regex headingRegex(
        "<h[1-3][^>]*>([\\s\\S]*?)</h[1-3]>",
        regex::icase
    );

    auto headingBegin =
        sregex_iterator(
            html.begin(),
            html.end(),
            headingRegex
        );

    auto headingEnd = sregex_iterator();

    int count = 0;

    for (
        auto it = headingBegin;
        it != headingEnd && count < 20;
        ++it
    ) {
        string heading =
            stripTags((*it)[1].str());

        if (!heading.empty()) {
            cout
                << ++count
                << ". "
                << heading
                << "\n";
        }
    }

    if (count == 0) {
        cout << "No headings found.\n";
    }

    cout << "\nLinks:\n";

    regex linkRegex(
        "<a[^>]*href=[\"']([^\"']+)[\"'][^>]*>([\\s\\S]*?)</a>",
        regex::icase
    );

    auto linkBegin =
        sregex_iterator(
            html.begin(),
            html.end(),
            linkRegex
        );

    auto linkEnd = sregex_iterator();

    count = 0;

    for (
        auto it = linkBegin;
        it != linkEnd && count < 20;
        ++it
    ) {
        string href = (*it)[1].str();
        string linkText = stripTags((*it)[2].str());

        if (!linkText.empty()) {
            cout
                << ++count
                << ". "
                << linkText
                << " -> "
                << href
                << "\n";
        }
    }

    if (count == 0) {
        cout << "No links found.\n";
    }

    return 0;
}
