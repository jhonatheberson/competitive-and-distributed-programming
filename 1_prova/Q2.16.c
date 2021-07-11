/*num computados*/
    float n = 10;

    //processador
    float p = 1;

    /*Tempo de execução serial em
    microsegundos*/
    float Tserial;

    /*Tempo de execução paralela em
    microsegundos*/
    float Tparalelo;

    for (int i=0;i<6;i++){
        for(int j=0;j<8;j++){
            Tserial = pow(n,2);
            Tparalelo = pow(n,2)/p + log2(p);
    cout << "O tempo de execucao serial sera " << Tserial << "us e o tempo de execucao paralela sera "<<Tparalelo
    <<"us para n = "<<n<<" e p = "<<p<<endl;
            p*=2;
        }
        p=1;
        n*=2;
    }