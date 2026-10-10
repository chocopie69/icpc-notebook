#include "../utilities/template.h"

#include "../../content/strings/Hashing.h"

#include <sys/time.h>
int main() {

	rep(it,0,10000) {
		int n = rand() % 10;
		int alpha = rand() % 10 + 1;
		string s;
		rep(i,0,n) s += (char)('a' + rand() % alpha);
		StringHash hi(s);
		set<string> strs;
		set<ull> hashes;

		// RollingHash
		rep(i,0,n) rep(j,i+1,n+1) {
			string sub = s.substr(i, j - i);
			ull hash = 0;
			for (char c : sub) hash = (hash*31+c-'a'+1)%1000000003;
			assert(hi.getHash(i+1, j) == (ll)hash);
			hashes.insert(hash);
			strs.insert(sub);
		}

		// getHashes
		rep(le,1,n+1) {
			rep(i,0,n-le+1) {
				StringHash window(s.substr(i,le));
				assert(window.getHash(1,le) == hi.getHash(i+1, i+le));
			}
		}

		// No collisions
		assert(sz(strs) == sz(hashes));
	}
	cout<<"Tests passed!"<<endl;
}
