#include <iostream>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    FILE* fp = (FILE*)userp;
    return fwrite(contents, size, nmemb, fp);
}

int main() {
    const char* url = "https://www.example.com/api/data.json";
    const char* savePath = "data.json";

    CURL* curl = curl_easy_init();
    if (curl) {
        FILE* fp = fopen(savePath, "wb");
        if (!fp) {
            std::cerr << "Nie można otworzyć pliku do zapisu." << std::endl;
            return 1;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        CURLcode res = curl_easy_perform(curl);
        fclose(fp);

        if (res == CURLE_OK) {
            std::cout << "Pobrano plik JSON do: " << savePath << std::endl;
        } else {
            std::cerr << "Błąd pobierania pliku: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    
    return 0;
}