/*
TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.
Design the encode and decode methods for the TinyURL service. There is no restriction on how your encode/decode algorithm should work.
You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.
*/

class Solution {
public:
    map<string, string> shorturlhash; //Store {Shortened URL : Expanded URL}
    map<string, string> longurlhash; //Store {Expanded URL : Shortened URL}
    
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        string http    = "http://";
        string https   = "https://";
        string www     = "www";
        string ret     = longUrl.substr(0, https.length()); //Substring out first 8 characters - length of "https://"
        string resUrl  = "";
        long int first = 0;
        long int i     = 0;
        long int size  = 0;
        long int ncode = 0;
        bool httpflag  = false;
        bool httpsflag = false;
        bool wwwflag   = false;
        int frequency[255] = {0};
        vector<char> charset;
        
        if (longurlhash.count(longUrl)) { //If the URL is already encoded before, return its Shortened URL
            return longurlhash[longUrl];
        }
        
        if (ret == https) { //Find if URL contains "https://" from the substring, if it contains then skip that part.
            first     = https.length() + 1; //Skip and start parsing URL after "https://"
            httpsflag = true;
        } else if (ret.substr(0, http.length()) == http) { //Find if contains "http://" from substring and skip it
            first    = http.length() + 1; //Skip and start parsing URL after "https://"
            httpflag = false;
        }
        
        if (longUrl.substr(first, www.length()) == www) { //Skip "www" if it contains
            first += www.length() + 1; //Skip and start parsing URL after "www"
            wwwflag = true;
        }
        
        for (i = first; i < longUrl.length(); i++) { //Find the frequency of each character in the main URL including '/', '.'.
            frequency[longUrl[i]]++;
            size++; //Find length of main URL
        }

        /* Extract 5 characters from the main URL such that they are equidistant from each other */
        for (i = first; i < longUrl.length(); i = i + (size / 5)) { 
            charset.push_back(longUrl[i]);
        }
        
        /* Find the sum of each character ASCII value * their no of occurence including ',','/' */
        for (i = 0; i < 255; i++) {
            if (frequency[i]) {
                ncode += (frequency[i] * i);
            }
        }
        
        /
        resUrl.append(to_string(size)); //First append the length of main URL
        resUrl.append(string(charset.begin(), charset.end())); //Then append the characters extracted as a string
        resUrl.append(to_string(ncode)); //Finally append the unique sum calculated
        
        longurlhash.insert(make_pair(longUrl, resUrl)); //Store {LongURL, Shortened URL}
        shorturlhash.insert(make_pair(resUrl, longUrl)); //Store {Shortened URL, Long URL}
        
        cout<<resUrl;
        
        return resUrl;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        return shorturlhash[shortUrl];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
