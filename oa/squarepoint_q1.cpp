#include <bits/stdc++.h>
using namespace std;

string fix(int tag, map<string, string>& mappings, string s){
    int n=s.size();

    // find 9 val
    int v9 = s.find("|9=")+3;
    int ev9 = s.find("|", v9);
    int len = stoi(s.substr(v9, ev9-v9));
    int initial_len = len;


    // find 10 val
    int v10 = s.rfind('='), ev10 = s.rfind('|');
    v10++;
    int csum = stoi(s.substr(v10, ev10-v10));
    cerr << csum << endl;
    
    // create tag for finding
    string findtag = "|";
    findtag.append(to_string(tag)); findtag.append("=");
    // cerr << findtag << endl;
    
    int ptr=0;
    while((ptr = s.find(findtag, ptr)) > 0){
        // cerr << ptr << endl;
        
        ptr+=findtag.size();
        int eptr = s.find("|", ptr);
        
        string olds = s.substr(ptr, eptr - ptr);
        string news = mappings[olds];
        // string news = "";
        // cerr << mappings[olds] << endl;
        
        if(news.size()==0){
            continue;
        }
        
        
        // cerr << olds << " " << news << endl;
        // cerr << s << endl;
        s.replace(ptr, eptr-ptr, news);
        // cerr << s << endl;
        
        // update len and csum
        len += news.size() - olds.size();
        for(char &c:news){
            csum +=c;
        }
        for(char &c:olds){
            csum -=c;
        }
    }
    for(char &c:to_string(len)){
        csum +=c;
    }
    for(char &c:to_string(initial_len)){
        csum -=c;
    }
    csum%=256;
    string rep = to_string(csum);
    while(rep.size()<3){
        rep.insert(0, "0");
    }
    
    
    cerr << csum << endl;
    // cerr << s << endl;
    ev9 = s.find("|", v9);
    s.replace(v9, ev9-v9, to_string(len));
    cerr << s << endl;
    v10 = s.rfind('=')+1;
    ev10 = s.rfind('|');
    s.replace(v10, ev10-v10, rep);
    cerr << s << endl;

    return s;


    // return findtag;

    // cerr << s.find('8') << endl;

    return 0;

}

vector<string> substituteFixMessage(int fixTag, map<string, string>& mappings, const vector<string>& FIXMessages) {
    int n_strings = FIXMessages.size();
    vector<string> answer(n_strings);
    for(int i =0; i<n_strings; i++){
        answer[i] = fix(fixTag, mappings, FIXMessages[i]);
    }

    return answer;
}


// --------------------------------------------------
// CPH / local testing driver
//
// Input format used ONLY for local testing:
//
// fixTag
// M
// oldValue newValue   (M lines)
// N
// FIX message         (N lines)
// --------------------------------------------------

int main() {
    int fixTag;
    cin >> fixTag;

    int M;
    cin >> M;

    map<string, string> mappings;

    for (int i = 0; i < M; i++) {
        string oldValue, newValue;
        cin >> oldValue >> newValue;
        mappings[oldValue] = newValue;
    }

    int N;
    cin >> N;

    vector<string> FIXMessages(N);

    for (int i = 0; i < N; i++) {
        cin >> FIXMessages[i];
    }

    vector<string> ans =
        substituteFixMessage(fixTag, mappings, FIXMessages);

    for (const string& msg : ans) {
        cout << msg << '\n';
    }

    return 0;
}