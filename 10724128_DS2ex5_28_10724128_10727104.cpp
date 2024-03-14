// 10724128 吳宇哲 10727104 王子威
// 【工具】–【編譯選項】–【編譯器】勾選【編譯時加入以下命令】
// 加入【-std=c++11】 ，即可運作。
#include <stdio.h>
#include <stdlib.h>
# include<fstream>
# include<string.h>
# include<iostream>
# include<vector>
# include<cstdlib>
# include<iomanip>
# include<stack>
#include<algorithm>
#include<math.h>
#include<queue>
#include <ctime>

using namespace std;


struct Data {
    char putID[10] ; // 發訊
    char getID[10] ; // 收訊
    float weight =0.0;
};// 讀取資料用的結構

struct SearchData {
    float weight =0.0;
    int index ;
};// 讀取資料用的結構

bool sortWeight( const Data &a, const Data &b ) {
        if (a.weight > b.weight)
            return true;
        else
            return false;
}

class External {
	private:
        vector<Data> temp1 ;
        vector<Data> temp2 ;
        vector<SearchData>searchList ;
    	string inputString ;
    	int excuTimeStart ;
    	int excuTimeEnd ;
    	int count ;
    public:
        void reset() {
            temp1.clear() ;
            temp2.clear() ;
            searchList.clear() ;
        }

		void readBin ( ) {
		    fstream theFile;
		    cout << endl << "Input a file number (e.g., 501, 502, ...): " ;
		    cin >> inputString ;
		    string fileName = "pairs" + inputString + ".bin" ;
  			int  dataNum, setNum ;
  			Data temp[200] ,temp1;
            theFile.open( fileName.c_str(), ios::in | ios::binary ) ;
  			if ( theFile.is_open() ) { // 檢查檔案是否打開
  			    theFile.seekg( 0, theFile.end ) ;
                setNum = theFile.tellg() / sizeof( temp ); // 讀取檔案次數
                dataNum = theFile.tellg() / sizeof( temp1 ); // 讀取檔案數量
                theFile.seekg( 0, theFile.beg ) ;
                if ( dataNum%200 != 0 ) {
                    setNum++ ;
                }
                for ( int i = 0 ; i < setNum ; i ++ ) {
                    theFile.read( (char*)&temp, sizeof(temp) ) ;
                    stable_sort( temp, temp+200, sortWeight ) ;
                    write( temp,setNum, i , dataNum ) ;
                    memset(temp, 0, sizeof(temp)) ;
                    //cout << setNum << endl ;
                    //cout << temp[i].getID <<"    "<< temp[i].weight<< endl ;
                }

    			theFile.close();
    			external( setNum ) ;
            }
            else {
                cout << "### The file does not exist! ###" <<endl ;
            }
		}

    vector<Data> merge(vector<Data> vec1, vector<Data> vec2) {
        vector< Data > returnTemp ;
        Data temp1 ;
        Data temp2 ;
        int vec1Size1 = vec1.size() ;
        int vec1Size2 = vec2.size() ;
        int walk1 = 0 , walk2 = 0 ;
        while ( vec1Size1 > walk1 || vec1Size2 > walk2) {
            if ( vec1Size1 > walk1 )
                temp1 = vec1.at(walk1) ;
            if ( vec1Size2 > walk2 )
                temp2 = vec2.at(walk2) ;
            if ( vec1Size2 ==  walk2 || ( temp1.weight >= temp2.weight&&vec1Size1 > walk1) ){
                returnTemp.push_back(temp1) ;
                walk1++ ;
                //cout << temp1.getID << "    "  << temp1.weight << "        1"<< endl ;

            }
            else {
                returnTemp.push_back(temp2) ;
                walk2++ ;
               // cout << temp2.getID << "    "  << temp2.weight<< "        2"<< endl ;

            }


        }


        return returnTemp ;
    }


        void external (  int numOfFile) {
            fstream readFile1;
            fstream readFile2;
            fstream outFile;
            vector< Data > returnTemp ;
            int needCount = 0 , dataNum, needSize;
            int readCount = 0, fileCount = 0, writeCount = 0 ;
            string fileName2 ;
            Data readTemp[200] ,dataTemp;
            while ( numOfFile != 1 ) {
                temp1.clear() ;
                temp2.clear() ;
                returnTemp.clear() ;
                string fileName1 = "sorted"+inputString+"_"+to_string(numOfFile) + "_" + to_string(fileCount) +".bin";
                if ( (fileCount + 1) != numOfFile ){
                    fileName2 = "sorted"+inputString+"_"+to_string(numOfFile) + "_" + to_string(fileCount+1) +".bin";
                    readFile2.open( fileName2.c_str(), ios::in | ios::binary ) ;
                }

                readFile1.open( fileName1.c_str(), ios::in | ios::binary ) ;

                if ( readFile1.is_open() ) { // 檢查檔案是否打開
                    readFile1.seekg( 0, readFile1.end ) ;
                    needCount = readFile1.tellg() / sizeof( readTemp ); // 讀取檔案次數
                    dataNum = readFile1.tellg() / sizeof( dataTemp ); // 讀取檔案數量
                    readFile1.seekg( 0, readFile1.beg ) ;
                    if ( dataNum%200!= 0)
                        needCount++ ;
                    for ( int i = 0 ; i < needCount ; i++) {
                        readFile1.read( (char*)&readTemp, sizeof(readTemp) ) ;
                        for ( int j = 0 ; j < 200 ; j++) {
                            if ( readTemp[j].weight!= 0)
                                temp1.push_back( readTemp[j] ) ;
                        }
                        memset(readTemp, 0, sizeof(readTemp)) ;
                    }



                }
                if ( readFile2.is_open() ) { // 檢查檔案是否打開
                    readFile2.seekg( 0, readFile2.end ) ;
                    needCount = readFile2.tellg() / sizeof( readTemp ); // 讀取檔案次數
                    dataNum = readFile2.tellg() / sizeof( dataTemp ); // 讀取檔案數量
                    readFile2.seekg( 0, readFile2.beg ) ;
                    if ( dataNum%200!= 0)
                        needCount++ ;
                    for ( int i = 0 ; i < needCount ; i++) {
                        readFile2.read( (char*)&readTemp, sizeof(readTemp) ) ;
                        for ( int j = 0 ; j < 200 ; j++) {
                            if ( readTemp[j].weight!= 0)
                                temp2.push_back( readTemp[j] ) ;
                        }
                        //temp2.push_back( readTemp ) ;
                        memset(readTemp, 0, sizeof(readTemp)) ;
                    }


                }

                if( readFile1.is_open() && readFile2.is_open()) {
                    returnTemp = merge( temp1,temp2) ;
                    write( returnTemp, numOfFile, writeCount) ;
                    readFile1.close();
                    readFile2.close();
                }
                else {
                    write( temp1, numOfFile, writeCount) ;
                    readFile1.close();
                }

                writeCount++ ;
                remove( fileName1.c_str() ) ;
                remove( fileName2.c_str() ) ;
                fileCount += 2 ;
               /* for ( int i = 0 ; i < returnTemp.size() ; i ++ ) {
                    cout << returnTemp.at(i).getID << "  " << returnTemp.at(i).weight << endl ;
                }*/
                if ( fileCount >= numOfFile) {
                    system("pause") ;
                    if ( numOfFile %2 != 0)
                        numOfFile = numOfFile/2 +1;
                    else
                         numOfFile = numOfFile/2 ;
                    fileCount = 0 ;
                    writeCount = 0 ;
                    cout << "Now there are " << numOfFile << " runs."<< endl ;
                }

            }


        }

        void write( vector<Data> temp, int numOfFile , int writeCount) {
            fstream newFile;
            int lineCount = 0 ;
            //newFile.open("sorted"+inputString+".bin", ios::out);
            int fileName = numOfFile/2;
            if ( numOfFile % 2!= 0 )
                fileName ++ ;
            newFile.open("sorted"+inputString+"_"+to_string(fileName) + "_" + to_string(writeCount) +".bin", fstream :: out | fstream :: binary ) ;
            Data writeTemp[200] ;
            int count = 0 ;
            int size = temp.size() ;
            for ( int j = 0 ; j < size ; j++ ) {
                writeTemp[count] = temp.at(j) ;
                count++ ;
                if ( (count ) % 200 == 0 ){
                    newFile.write( (char*)&writeTemp, sizeof(writeTemp[0])*200 ) ;
                    count = 0 ;
                    memset(writeTemp, 0, sizeof(writeTemp)) ;
                    //cout << writeCount << endl ;
                }


            }
            if ( size%200 != 0 ) {
                newFile.write( (char*)&writeTemp, sizeof(writeTemp[0])*count ) ;
            }

            memset(writeTemp, 0, sizeof(writeTemp)) ;
            newFile.close() ;
            //cout << "done!" << endl ;
        }

        void write( Data input[200], int size, int fileCount, int dataNum) {
            fstream newFile;
            //newFile.open("sorted"+inputString+".bin", ios::out);
            int needSize = dataNum - ( fileCount*200) ;
            if ( needSize > 200)
                needSize = 200 ;
            newFile.open("sorted"+inputString+"_"+to_string(size) + "_" + to_string(fileCount) +".bin", fstream :: out | fstream :: binary ) ;
            for ( int i = 0 ; i < needSize ; i ++ ) {

            newFile.write( (char*)&input[i], sizeof(input[i]) ) ;

        } // end for


            newFile.close() ;
            //cout << "done!" << endl ;
        }



        void renameFile() {
            //cout << "sorted" << inputString << "_1_0.bin" << endl ;
            remove( ("sorted" + inputString + ".bin").c_str() ) ;
            rename( ("sorted" + inputString + "_1_0.bin").c_str(), ("sorted" + inputString + ".bin").c_str() ) ;
        }

        void search () {
            fstream readFile;
            SearchData searchTemp ;
            int needCount, dataNum, readCount = 0, outputCount = 1;
            float checkNum = 2;
            Data readTemp[200] ,dataTemp;
            readFile.open( ("sorted" + inputString + ".bin").c_str(), ios::in | ios::binary ) ;
            temp1.clear() ;
            if ( readFile.is_open() ) { // 檢查檔案是否打開
                readFile.seekg( 0, readFile.end ) ;
                needCount = readFile.tellg() / sizeof( readTemp ); // 讀取檔案次數
                dataNum = readFile.tellg() / sizeof( dataTemp ); // 讀取檔案數量
                readFile.seekg( 0, readFile.beg ) ;
                if ( dataNum%200!= 0)
                    needCount++ ;
                for ( int i = 0 ; i < needCount ; i++) {
                    readFile.read( (char*)&readTemp, sizeof(readTemp) ) ;
                    for ( int j = 0 ; j < 200 ; j++) {
                        if ( readTemp[j].weight != checkNum&& readTemp[j].weight != 0){
                            cout << "[" << outputCount << "] (" <<readTemp[j].weight << ", " << readCount << ")"<< endl ;
                            searchTemp.index = readCount ;
                            searchTemp.weight = readTemp[j].weight ;
                            searchList.push_back( searchTemp) ;
                            checkNum  =readTemp[j].weight ;
                            outputCount++ ;
                        }

                        readCount++ ;
                    }
                    memset(readTemp, 0, sizeof(readTemp)) ;
                }
            }

        }

        void rangeSearch() {
            fstream readFile;
            int needCount, dataNum, readCount = 0, outputCount = 1;
            float checkNum = 2;
            Data readTemp[200] ,dataTemp;
            bool inputCheck = true ;
            int stopPoint ;
            float range ;
            while ( inputCheck ) {
                cout << "Please input a threshold in the range [0,1]: " ;
                cin >> range ;
                if ( range > 0 && range <= 1)
                    inputCheck = false ;
            }
            for ( int i = 0 ; i< searchList.size() ; i ++ ) {
                if ( range > searchList.at(i).weight ) {
                    stopPoint = searchList.at(i).index ;
                    break ;
                }
            }
            readFile.open( ("sorted" + inputString + ".bin").c_str(), ios::in | ios::binary ) ;
            if ( readFile.is_open() ) { // 檢查檔案是否打開
                readFile.seekg( 0, readFile.end ) ;
                needCount = readFile.tellg() / sizeof( readTemp ); // 讀取檔案次數
                dataNum = readFile.tellg() / sizeof( dataTemp ); // 讀取檔案數量
                readFile.seekg( 0, readFile.beg ) ;
                if ( dataNum%200!= 0)
                    needCount++ ;
                for ( int i = 0 ; i < needCount ; i++) {
                    readFile.read( (char*)&readTemp, sizeof(readTemp) ) ;
                    for ( int j = 0 ; j < 200 ; j++) {
                        if ( readTemp[j].weight != 0){
                            cout << "[" << outputCount << "] " <<readTemp[j].putID << "    " << readTemp[j].getID << "    " << readTemp[j].weight << "    "<< endl ;

                            if ( outputCount >= stopPoint)
                            break ;
                            outputCount++ ;
                        }

                        readCount++ ;
                    }
                    //cout << outputCount <<endl ;
                    if ( outputCount >= stopPoint)
                           break ;
                    memset(readTemp, 0, sizeof(readTemp)) ;
                }
            }
        }
};

int main(void) {
	int command = -1;
	External ex ;
    bool check = false ;
    bool check2 = false;
	while ( command != 0 ) {
		cout << endl;
		cout << "************* On-machine  *************\n"
			 << "* 0. QUIT                             *\n"
			 << "* 1. External Merge Sort on a Big File*\n"
			 << "* 2.Construction of Primary Index     *\n"
			 << "* 3: Range Search by Primary Index    *\n"
			 << "***************************************\n\n"
			 << "Please input your command :  " ;
		cin >> command;
		if ( command == 1 ) {
            float time = clock() ;
            ex.reset() ;
            ex.readBin() ;
            ex.renameFile() ;
            time = clock() - time ;
            cout << endl << "The Execution Time : " << time << " ms" << endl ;
			cout << endl ;
			check = true ;
		}
		else if ( command == 2 ) {
            if ( check ) {
                ex.search() ;
                check2 = true ;
            }
            else {
                cout << "### There is no graph and choose 1 first. ###" << endl ;
            }

		}
		else if ( command == 3 ) {
            if ( check && check2) {
                ex.rangeSearch() ;
            }
            else {
                cout << "### There is no graph and choose 1 and 2 first. ###" << endl ;
            }

		}


		else if ( command != 0 ) {
			cout << endl << "Error !!! 請輸入正確的指令!!!\n\n" ;
		}
	}

	cout << endl << "結束!" << endl;
}
