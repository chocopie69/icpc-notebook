#include "../utilities/template.h"

#include "../../content/data-structures/RMQ.h"

int main() {
	srand(2);
	rep(N,0,100) {
		vi v(N+1);
		rep(i,1,N+1) v[i] = rand()%2001-1000;
		SparseTable rmq(v);
		rep(i,1,N+1) rep(j,i,N+1) {
			assert(rmq.getMin(i,j) == *min_element(v.begin()+i,v.begin()+j+1));
			assert(rmq.getMax(i,j) == *max_element(v.begin()+i,v.begin()+j+1));
		}
	}
	cout<<"Tests passed!"<<endl;
}
