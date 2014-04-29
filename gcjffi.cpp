#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

unsigned int mkdircount;
		
vector<string> SplitString( string s )
{
	istringstream iss( s );
	string token;
	vector<string> result;
	
	while( getline( iss, token, '/' ) )
	{
		if( token != "" )
		{
			result.push_back( token );
		}
	}
	
	return result;
}

string GetFirstDirName( string s )
{
	vector<string> token;
	token = SplitString( s );
	return token[0];
}

string EraseFirstDir( string s )
{
	istringstream iss(s);
	string token;
	token = "";
	
	while( token == "" )
	{
		getline( iss, token, '/' );
	}
	iss >> token;
	if( s.compare(token) == 0 )
		return "";
	else
		return token;
}

class Dir
{
	private:
		string Name;
		vector<Dir*> ChildDir;
		bool IsThereChild( string s )
		{
			for( unsigned int i=0; i<this->ChildDir.size(); i++ )
			{
				if( s.compare( this->ChildDir[i]->OutputName() ) == 0 )
					return true;
			}
			return false;
		}
		Dir* GetChildPointer( string s )
		{
			for( unsigned int i=0; i<this->ChildDir.size(); i++ )
			{
				if( s.compare( this->ChildDir[i]->OutputName() ) == 0 )
					return ChildDir[i];
			}
			return NULL;
		}
	public:
		void InputName( string s )
		{
			this->Name = s;
		}
		
		string OutputName( void )
		{
			return this->Name;
		}
		
		void InputDirs( string d )
		{
			if( d == "" )
			{
				return;
			}
			
			if( d.front() == '/' )
			{
				d.erase( d.begin() );
			}
			
			string chdname;
			
			chdname = GetFirstDirName( d );
			//cout << "chdname: " << chdname << endl;
			
			if( this->IsThereChild( chdname ) )
			{
				Dir* temp;
				string NextDir;
				
				temp = this->GetChildPointer( chdname );
				NextDir = EraseFirstDir( d );
				//cout << "NextDir: " << NextDir << endl;
				if( NextDir == "" )
					return;
				else
					temp->InputDirs( NextDir );
			}
			else
			{
				//cout << chdname << " ," << mkdircount << endl;
				Dir* temp;
				temp = new Dir;
				//cout << "d: " << d << endl;
				mkdircount++;
				//cout << "count: " << mkdircount << endl;
				this->ChildDir.push_back( temp );
				temp->InputName( chdname );
				
				string NextDir;
				NextDir = EraseFirstDir( d );
				//cout << "NextDir: " << NextDir << endl;
				if( NextDir == "" )
				{
					return;
				}
				else
					temp->InputDirs( NextDir );
			}
		}
};

int main( int argc, char** argv )
{
	int T, N, M;
	
	ifstream myfile;
	
	myfile.open( argv[1] );
	
	myfile >> T;

	for( int i=0; i<T; i++ )
	{
		myfile >> N >> M;
		
		Dir dirs;
		dirs.InputName( "/" );
		
		for( int j=0; j<N; j++ )
		{
			string temp;
			myfile >> temp;
			//temp.erase( temp.begin() );
			dirs.InputDirs( temp );
		}
		
		mkdircount = 0;
		for( int k=0; k<M; k++ )
		{
			string temp;
			myfile >> temp;
			//temp.erase( temp.begin() );
			dirs.InputDirs( temp );
		}
		cout << "Case #" << i+1 << ": " << mkdircount << endl;

}
	
	myfile.close();
	return 0;
}
