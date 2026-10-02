from urllib.parse import urlparse

def main():
    try:
        import requests
        from bs4 import BeautifulSoup
    except ImportError:
        print("Install dependencies: pip install -r requirements.txt")
        return

    print("=== Interactive Web Scraper ===")
    url = input("Enter a public http/https URL: ").strip()
    parsed = urlparse(url)

    if parsed.scheme not in {"http", "https"} or not parsed.netloc:
        print("Invalid URL.")
        return

    try:
        response = requests.get(
            url,
            timeout=10,
            headers={"User-Agent": "CognifyzEducationalScraper/1.0"}
        )
        response.raise_for_status()
    except requests.RequestException as exc:
        print("Request failed:", exc)
        return

    soup = BeautifulSoup(response.text, "html.parser")
    title = soup.title.get_text(" ", strip=True) if soup.title else "No title"
    print("\nTitle:", title)

    print("\nHeadings:")
    headings = [
        h.get_text(" ", strip=True)
        for h in soup.find_all(["h1", "h2", "h3"])
        if h.get_text(" ", strip=True)
    ]
    if not headings:
        print("No headings found.")
    for i, heading in enumerate(headings[:20], 1):
        print(f"{i}. {heading}")

    print("\nLinks:")
    links = []
    for a in soup.find_all("a", href=True):
        text = a.get_text(" ", strip=True)
        if text:
            links.append((text, a["href"]))
    if not links:
        print("No links found.")
    for i, (text, href) in enumerate(links[:20], 1):
        print(f"{i}. {text} -> {href}")

if __name__ == "__main__":
    main()
