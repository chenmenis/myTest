#include<sstream>
#include<iostream>
#include<algorithm>
#include<vector>
#include<deque>
#include<unordered_map>

using namespace std;

struct Pds{

Pds(double Pd,double Sev):pd(Pd),sev(Sev){};

double pd;
double sev;

};

void permuteUtility(vector<double> &res, vector<double> &pd,int k,vector<int> &ps,vector<double> &sev, vector<Pds> &result){

    if(k == pd.size()) {
        double sumSev(0);
        double sumPds(1);
        for(int i = 0; i < res.size();i++){
            cout << (ps[i] ? "P":"1-P" )<<":" << res[i] << ",";
           sumPds = sumPds* (ps[i] ? pd[i]: 1- pd[i]);
           sumSev += ps[i] ? sev[i] : 0;

        }

        result.push_back(Pds(sumPds,sumSev));

        cout << ", PD: " << sumPds;

        cout << ", sumSev: " << sumSev;

        cout << endl;
        //res.clear();
        return;
    }

        double tpd = pd[k];
        res[k]=(tpd);
        ps[k] = 1;
        permuteUtility(res,pd,k+1,ps,sev,result);

        res[k]= (1-tpd);
        ps[k] = 0;
        permuteUtility(res,pd,k+1,ps,sev,result);

}
bool myfunctionByPD (const Pds &i, const Pds &j) { return (i.pd <j.pd); }
bool myfunctionBySev (const Pds &i, const Pds &j) { return (i.sev <j.sev); }


void readCSV(std::istream &input, std::vector< std::vector<std::string> > &output)
{
	std::string csvLine;
	// read every line from the stream
	while( std::getline(input, csvLine) )
	{
		std::istringstream csvStream(csvLine);
		std::vector<std::string> csvColumn;
		std::string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while( std::getline(csvStream, csvElement, ',') )
		{
			csvColumn.push_back(csvElement);
		}
		output.push_back(csvColumn);
	}
}

bool readFile(string InfileName,vector<double> &pds, string ofileName, map<int,double> &candOutput){
    ifstream pd(InfileName);
    ifstream OutfileName(ofileName);
    if(!pd || !OutfileName){
            cout << "file not found" <<endl;
            return false;

    }
    pds.clear();
    double inputPD

    while(pd >> inputPD){
            cout << "inputpd " << inputPD;
            pds.push_back(inputPD);
    }

    double sev,probDf;

    while(OutfileName >> sev >> probDf){
            cout << " sev " << sev << " probdef " << probDf << endl;
            candOutput[int(sev*100)]= probDf;
    }
    return true;

}

int main(){
    vector<double> pds = {0.2,0.4,0.6};

    map<int,double> candMap;

    if(readFile("test1output.csv",pds,"test1output.csv",candMap)){


    }
    return 0;


    vector<double> sev = {0.02,0.04,0.01};

    vector<double> res(pds.size());
    vector<int> ps(pds.size(),1);
    vector<Pds> result;
    permuteUtility(res,pds,0,ps,sev,result);


    cout << " sort by SEV" << endl;
    sort(result.begin(),result.end(),myfunctionBySev);
    for(auto x:result)
        cout << " PD : " << x.pd << " SEV: " << x.sev << endl;
    cout << " sort by PD" << endl;
    sort(result.begin(),result.end(),myfunctionByPD);
    for(auto x:result)
        cout << " PD : " << x.pd << " SEV: " << x.sev << endl;

    cout << "asdf " << endl;
    return 0;
}
