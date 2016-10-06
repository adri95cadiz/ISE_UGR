#include<benchmark.h>

	const int wrop=500;

	double Benchmark::writeOp(){
  		double t_before,t_after;
		double write_time;
		int n_data=1000000,i;
		int dat[n_data];
		for(i=1;i<=n_data;i++) 
			dat[i] = i;
		i=0;
		cout<<"Iniciamos el test de escritura en la memoria USB."<<endl;
		cout<<"Escribiendo en la memoria puede demorarse..."<<endl;
		string aux = dev+"/temp.dat";		
		#pragma omp parallel sections
		{
			t_before = omp_get_wtime();
			ofstream salida(aux.c_str(), ios::out|ios::binary);
			for(i=0;i<wrop;i++)
				salida.write(reinterpret_cast<const char*>(dat),n_data*sizeof(int)); 
			salida.close();
			t_after = omp_get_wtime();
			#pragma omp section
			{
				int i_local = -5;
				while(i!=wrop){
					if(i_local != i){
						cout << (i*100)/wrop << "% ";
						i_local=i;
					}
					cout.flush();
					sleep(2);
				}
			}
		}
		
		write_time = t_after - t_before;
		cout<<"\nTiempo empleado en la escritura en la memoria: "<<write_time<<" s."<<endl;
		return write_time;
	}

	double Benchmark::readOp(){
  		double t_before,t_after;
		double read_time;
		int n_data=1000000;
		int dat[n_data],i;
		string aux = dev+"/temp.dat";		
		for(i=1;i<=n_data;i++) 
			dat[i] = i;
		i=0;
		cout<<"Iniciamos el test de lectura en la memoria USB."<<endl;
		cout<<"Leyendo de la memoria USB puede demorarse..."<<endl;
		#pragma omp parallel sections
		{
		 	t_before = omp_get_wtime();
			ifstream entrada(aux.c_str(), ios::in|ios::binary);
			for(i=0;i<wrop;i++)
				entrada.read(reinterpret_cast<char*>(dat),n_data*sizeof(int)); 
			entrada.close();
			t_after = omp_get_wtime();
			#pragma omp section
			{
				int i_local = -5;
				while(i!=wrop){
					if(i_local != i){
						cout << (i*100)/wrop << "% ";
						i_local=i;
					}
					cout.flush();
					sleep(2);
				}
			}
		}

		read_time = t_after - t_before;
		cout<<"\nTiempo empleado en la lectura de la memoria: "<<read_time<<" s."<<endl;
		
		return read_time;
	}

	double Benchmark::lwriteOp(){
  		double t_before,t_after;
		double write_time, total_time=0;
		int n_data=25000,i,j;
		int dat[n_data];
		for(i=1;i<=n_data;i++) 
			dat[i] = i;
		cout<<"Iniciamos el test de escritura de muchos archivos en la memoria USB."<<endl;
		cout<<"Escribiendo en la memoria muchos archivos puede demorarse..."<<endl;
		string aux = dev+"/temp.dat";		
		#pragma omp parallel sections
		{
			for(j=0; j < 100;j++){
				aux = dev+"/temp"+itos(j)+".dat";
				t_before = omp_get_wtime();
				ofstream salida(aux.c_str(), ios::out|ios::binary);
				for(i=0;i<wrop;i++)
					salida.write(reinterpret_cast<const char*>(dat),n_data*sizeof(int)); 
				salida.close();
				t_after = omp_get_wtime();
				total_time += (t_after-t_before);
			}
			#pragma omp section
			{
				int j_local = -5;
				while(j!=100){
					if(j_local != i){
						cout << j << "% ";
						j_local=j;
					}
					cout.flush();
					sleep(2);
				}
			}
		}
		
		write_time = total_time;
		cout<<"\nTiempo empleado en la escritura en la memoria: "<<write_time<<" s."<<endl;
		return write_time;
	}

	double Benchmark::lreadOp(){
  		double t_before,t_after;
		double read_time, total_time=0;
		int n_data=25000,i,j;
		int dat[n_data];
		for(i=1;i<=n_data;i++) 
			dat[i] = i;
		cout<<"Iniciamos el test de lectura de muchos archivos en la memoria USB."<<endl;
		cout<<"Leyendo de la memoria muchos archivos puede demorarse..."<<endl;
		string aux = dev+"/temp.dat";		
		#pragma omp parallel sections
		{
			for(j=0; j < 100;j++){
				aux = dev+"/temp"+itos(j)+".dat";
				t_before = omp_get_wtime();
				ifstream entrada(aux.c_str(), ios::in|ios::binary);
				for(i=0;i<wrop;i++)
					entrada.read(reinterpret_cast<char*>(dat),n_data*sizeof(int)); 
				entrada.close();
				t_after = omp_get_wtime();
				total_time += (t_after-t_before);
			}
			#pragma omp section
			{
				int j_local = -5;
				while(j!=100){
					if(j_local != i){
						cout << j << "% ";
						j_local=j;
					}
					cout.flush();
					sleep(2);
				}
			}
		}
		
		read_time = total_time;
		cout<<"\nTiempo empleado en la lectura en la memoria: "<<read_time<<" s."<<endl;
		return read_time;
	}

	double Benchmark::lreadwriteOp(){
  		double t_before,t_after;
		double read_time, total_time=0;
		int n_data=25000,i,j;
		int dat[n_data];
		for(i=1;i<=n_data;i++) 
			dat[i] = i;
		cout<<"Iniciamos el test de escritura/lectura de muchos archivos en la memoria USB."<<endl;
		cout<<"Escribiendo y leyendo de la memoria muchos archivos puede demorarse..."<<endl;
		string aux = dev+"/temp.dat";		
		#pragma omp parallel sections
		{
			for(j=0; j < 100;j++){
				aux = dev+"/temp"+itos(j)+".dat";
				t_before = omp_get_wtime();
				ofstream salida(aux.c_str(), ios::out|ios::binary);
				ifstream entrada(aux.c_str(), ios::in|ios::binary);
				for(i=0;i<wrop;i++){
					salida.write(reinterpret_cast<const char*>(dat),n_data*sizeof(int));
					entrada.read(reinterpret_cast<char*>(dat),n_data*sizeof(int)); 
				}
				entrada.close();
				salida.close();
				t_after = omp_get_wtime();
				total_time += (t_after-t_before);
			}
			#pragma omp section
			{
				int j_local = -5;
				while(j!=100){
					if(j_local != i){
						cout << j << "% ";
						j_local=j;
					}
					cout.flush();
					sleep(2);
				}
			}
		}
		
		read_time = total_time;
		cout<<"\nTiempo empleado en la escritura/lectura en la memoria: "<<read_time<<" s."<<endl;
		return read_time;
	}

	double Benchmark::readwriteOp(){
		double t_before,t_after;
		double write_time;
		int n_data=1000000,i;
		int dat[n_data];
		for(i=1;i<=n_data;i++) 
			dat[i] = i;
		i=0;
		cout<<"Iniciamos el test de escritura/lectura en la memoria USB."<<endl;
		cout<<"Escribiendo y leyendo en la memoria puede demorarse..."<<endl;
		string aux = dev+"/temp.dat";		
		#pragma omp parallel sections
		{
			t_before = omp_get_wtime();
			ofstream salida(aux.c_str(), ios::out|ios::binary);
			ifstream entrada(aux.c_str(), ios::in|ios::binary);
			for(i=0;i<wrop;i++){
				salida.write(reinterpret_cast<const char*>(dat),n_data*sizeof(int));
				entrada.read(reinterpret_cast<char*>(dat),n_data*sizeof(int)); 
			}
			entrada.close();
			salida.close();
			t_after = omp_get_wtime();
			#pragma omp section
			{
				int i_local = -5;
				while(i!=wrop){
					if(i_local != i){
						cout << (i*100)/wrop << "% ";
						i_local=i;
					}
					cout.flush();
					sleep(2);
				}
			}
		}
		
		write_time = t_after - t_before;
		cout<<"\nTiempo empleado en la escritura/lectura en la memoria: "<<write_time<<" s."<<endl;
		return write_time;
	}

	void Benchmark::usbInfo(){
		char user_aux[100];
		cout << "Introduzca el nombre de su memoria USB: ";
		cin >> usbName;
		cout << "Se van a recopilar datos de la memoria, para ello identifique de la siguiente salida su memoria e indique su bus y numero de dispositivo: " << endl;
		system("lsusb");
		cout << "Bus: ";
		cin >> usbBus;
		cout << "Device: ";
		cin >> usbDevice;
		string ord = "lsusb -D /dev/bus/usb/"+usbBus+"/"+usbDevice+" >> usbInfo";
		system(ord.c_str());
		
		getlogin_r(user_aux, 100);
		string user(user_aux);
		ord = "/media/"+user+"/"+usbName;
		dev = ord;
	}
	
	Benchmark::Benchmark(int levels){
		this->levels = levels;
		last_operation = new double*[15];
		last_operation2 = new double*[15];
		for(int i=0; i < 15; i++){
			last_operation[i] = new double[levels];
			last_operation2[i] = new double[levels];
		}
		for(int i=0; i < 15; i++)
			for(int j=0; j < levels; j++){
				last_operation[i][j]=0;
				last_operation2[i][j]=0;
			}
	}

	Benchmark::~Benchmark(){
		for(int i=0; i < 15; i++){
			delete [] last_operation[i];
			delete [] last_operation2[i];
		}
		delete [] last_operation;
		delete [] last_operation2;
	}

	void Benchmark::showLastBenchmark(double ** oper){
		cout << endl;
		for(int i=0; i < 15; i++){
			for(int j=0; j < levels; j++)
				cout << oper[i][j] << " ";
		cout << endl;
		}
	} 

	double Benchmark::mbps(double time, double file_size){
		return file_size/time;
	}

	void Benchmark::saveData(int exp){
		ofstream file ("data.csv",ios::out);
		file.seekp(0, ios::beg);
		if(exp == 1){
			file << "Experimento 1," << endl;		
		
			for(int i = 0; i<15; i++){
				file << i << ", ";
				for(int j =0; j<levels; j++){
					file << last_operation[i][j] << ", ";
				}
				file << endl;
				if(i%4==0 && i!=0)
					file << endl;
			}
		
			file << endl;

			for(int i = 0; i<15; i++){
				file << i << ", ";
				for(int j =0; j<levels; j++){
					file << mbps(last_operation[i][j],2048.0) << ", ";
				}
				file << endl;
				if(i%4==0 && i!=0)
					file << endl;
			}
			file << endl;
			}
		else{
			file << "Experimento 2," << endl;		

			for(int i = 0; i<15; i++){
				file << i << " ";
				for(int j =0; j<levels; j++){
					file << last_operation2[i][j] << ", ";
				}
				file << endl;
				if(i%4==0 && i!=0)
					file << endl;
			}

			file << endl;

			for(int i = 0; i<15; i++){
				file << i << " ";
				for(int j =0; j<levels; j++){
					file << mbps(last_operation2[i][j],5000.0) << ", ";
				}
				file << endl;
				if(i%4==0 && i!=0)
					file << endl;
			}
		}
		file.close();
	}

	void Benchmark::usbMemoryTest(int level, int exp){
		double write_time, read_time, readwrite_time,total;
		usbInfo();
		if(exp == 1){
			cout << "//======1er experimento, Escritura, Lectura, Escritura/Lectura un archivo 2.00 GB=========//" << endl;
			for(int i = 0; i < 5; i++){
				write_time = writeOp();
				read_time = readOp();
				readwrite_time = readwriteOp();
				total =  write_time+read_time;
				last_operation[i][level]=write_time;
				last_operation[i+5][level]=read_time;
				last_operation[i+10][level]=readwrite_time;
				showLastBenchmark(last_operation);
				cout << "Megas por segundo: " << mbps(last_operation[i][level], 2048.0) << endl;
				cout << "Megas por segundo: " << mbps(last_operation[i+5][level], 2048.0) << endl;
				cout << "Megas por segundo: " << mbps(last_operation[i+10][level], 2048.0) << endl;
				//----------Clean----------------------------
				string clean = "rm "+dev+"/temp.dat";
				system(clean.c_str());
			}
		}
		else{
			for(int i = 0; i < 5; i++){
				cout << "//======2o experimento, Escritura, Lectura, Escritura/Lectura 100 archivos 50.00 MB=========//" << endl;
				write_time = lwriteOp();
				read_time = lreadOp();
				readwrite_time = lreadwriteOp();
				total =  write_time+read_time;
				last_operation2[i][level]=write_time;
				last_operation2[i+5][level]=read_time;
				last_operation2[i+10][level]=readwrite_time;
				showLastBenchmark(last_operation2);
				cout << "Megas por segundo: " << mbps(last_operation2[i][level], 5000.0) << endl;
				cout << "Megas por segundo: " << mbps(last_operation2[i+5][level], 5000.0) << endl;
				cout << "Megas por segundo: " << mbps(last_operation2[i+10][level], 5000.0) << endl;
				//----------Clean----------------------------
				string clean = "rm "+dev+"/temp*.dat";
				system(clean.c_str());
				cout << "Tiempo total invertido " << write_time+read_time << endl;
			}
		}
	}
