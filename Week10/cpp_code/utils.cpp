#include "utils.h"


// ------- STATISTICA DI UN VETTORE -------

// calcolo del modulo di un vettore
double get_mod(vector<double>& v){
	double mod = 0;
	for(auto& el : v)
		mod += el*el;
	return sqrt(mod);
}

// calcolo della somma degli elementi di un vettore
double get_sum(vector<double>& v){
	double sum = 0;
	for(auto& el : v)
		sum += el;
	return sum;
}

// calcolo della media di un vettore
double get_mean(vector<double>& v){
	return get_sum(v)/v.size();
}

// calcolo della varianza di un vettore (media empirica)
double get_var(vector<double>& v){
	double sum = 0, m = get_mean(v);
	for(auto& el : v)
		sum += pow(el - m, 2);
	return sum/v.size();
}

// calcolo della varianza di un vettore (media teorica)
double get_var(vector<double>& v, double m){
	double sum = 0;
	for(auto& el : v)
		sum += pow(el - m, 2);
	return sum/v.size();
}


// calcolo della varianza di un vettore (media empirica)
double get_dev_std(vector<double>& v){
	return sqrt(get_var(v));
}

// calcolo della varianza di un vettore (media teorica)
double get_dev_std(vector<double>& v, double m){
	return sqrt(get_var(v, m));
}


// calcolo del chi quadro (su intervallo reale)
double get_chi_sq(vector<double>& v, double m, double min, double max, int n_int){
	
	double dx = (max - min)/double(n_int);
	vector<double> count;
	for(int i=0; i<n_int; i++)
		count.push_back(0);
	
	sort(v.begin(), v.end());
	for(auto& el : v){
		for(int i=0; i<n_int; i++){
         		if( el >= min + i*dx and el < min + (i+1)*dx ){
         			count[i] ++;
         			break;
         		}
         	}
	}
	
	return get_var(count, m) * n_int/m;
}

// ottiene l'indice di un elemento del vettore
int get_index(vector<double> v, double el)
{
    auto it = find(v.begin(), v.end(), el);
  
    // If element was found
    if (it != v.end()) 
    {
        // calculating the index of K
        int index = it - v.begin();
        return index;
    }
    else 
	{
        // If the element is not present in the vector
        return -1;
    }
}

// salva un vettore
void save(vector<double>& v, string filename, string head){

	ofstream fout(filename);
	
	fout << head << endl;
	for(auto& el : v)
		fout << el << endl;
	
	fout.close();
}

// salva due vettori un vettore
void save(vector<double>& v1, vector<double>& v2, string filename, string head1, string head2){

	if(v1.size() != v2.size()){
		cout << "Errore: vettori di taglie diverse!" << endl;
		exit(0);
	}

	ofstream fout(filename);
	
	fout << head1 << "\t" << head2 << endl;
	for(int i=0; i<int(v1.size()); i++)
		fout << v1[i] << "\t" << v2[i] << endl;
	
	fout.close();
}


// swap elementi i-j
void swap(vector<double>& v, int i, int j)
{
	if(i<0 || j<0)
	{
		cout << "Error (swap): i and j must be non-negative. Exit." << endl;
		exit(2);
	}
	else if(i>=int(v.size()) || j>=int(v.size()))
	{
		cout << "Error (swap): i and j must not exceed vector size. Exit." << endl;
		exit(2);
	}

	double copy = v[i];
	v[i] = v[j];
	v[j] = copy;
}



// ------- OPERAZIONI TRA VETTORI -------

// somma tra vettori
vector<double> operator+ (const vector<double>& v1, const vector<double>& v2){

	if(v1.size() != v2.size()){
		cout << "Errore: somma di due vettori di taglie diverse!" << endl;
		exit(0);
	}

	vector<double> v;
	for(int i=0; i<int(v1.size()); i++)
		v.push_back(v1[i] + v2[i]);

	return v;
	
}

// somma tra vettore e costante
vector<double> operator+ (const vector<double>& v1, double k){

	vector<double> v;
	for(int i=0; i<int(v1.size()); i++)
		v.push_back(v1[i] + k);

	return v;
	
}

// differenza tra vettori
vector<double> operator- (const vector<double>& v1, const vector<double>& v2){

	if(v1.size() != v2.size()){
		cout << "Errore: sottrazione di due vettori di taglie diverse!" << endl;
		exit(0);
	}

	vector<double> v;
	for(int i=0; i<int(v1.size()); i++)
		v.push_back(v1[i] - v2[i]);

	return v;
	
}

// differenza tra vettore e costante
vector<double> operator- (const vector<double>& v1, double k){

	vector<double> v;
	for(int i=0; i<int(v1.size()); i++)
		v.push_back(v1[i] - k);

	return v;
	
}

// prodotto tra vettori
double operator* (const vector<double>& v1, const vector<double>& v2){

	if(v1.size() != v2.size()){
		cout << "Errore: prodotto di due vettori di taglie diverse!" << endl;
		exit(0);
	}

	double prod = 0;
	for(int i=0; i<int(v1.size()); i++)
		prod += v1[i] * v2[i];

	return prod;
	
}

// prodotto tra vettore e costante
vector<double> operator* (double k, const vector<double>& v1){

	vector<double> v;
	for(auto& el : v1)
		v.push_back(k * el);

	return v;
	
}

// divisione tra vettori
vector<double> operator/ (const vector<double>& v1, const vector<double>& v2){

	if(v1.size() != v2.size()){
		cout << "Errore: divisione tra due vettori di taglie diverse!" << endl;
		exit(0);
	}

	vector<double> v;
	for(int i=0; i<int(v1.size()); i++){
		
		if(v2[i] == 0){
			cout << "Errore: divisione per elemento nullo! (elemento " << i << "-esimo" << endl;
			exit(0);
		}
		
		v.push_back( v1[i]/v2[i] );
		
	}

	return v;
	
}

// divisione tra vettore e costante
vector<double> operator/ (const vector<double>& v1, double k){

	vector<double> v;
	
	if(k == 0){
		cout << "Errore: la costante deve essere non nulla!" << endl;
		exit(0);
	}
	
	for(auto& el : v1)
		v.push_back(el / k);

	return v;
}

//elevazione a potenza degli elementi del vettore
vector<double> operator^ (const vector<double>& v1, double esp){

	vector<double> v;
	for(int i=0; i<int(v1.size()); i++)
		v.push_back(pow(v1[i], esp));

	return v;
}