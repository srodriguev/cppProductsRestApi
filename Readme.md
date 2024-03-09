
- *Instalar todas las depdendencias necesarias. como g++ (compilador c++)*
    _sudo apt update_

    _sudo apt install g++ libboost-all-dev libssl-dev_

- *Instala  libcpprest-dev*

    _sudo apt install libcpprest-dev_

- *Para verificarla*

    _dpkg -l | grep libcpprest_

- *Compilar el programa*

    En la carpeta src:
    
    _g++ -std=c++11 main.cpp -o productsapp -lcpprest -lboost_system -lssl -lcrypto_

    -std=c++11: Especifica el estándar de C++ a usar, necesario para algunas características de C++ usadas con libcpprest.
    main.cpp: El nombre del source.cpp
    - o productsapp: Especifica el nombre del archivo de salida ejecutable. Puedes cambiar my_service por cualquier otro nombre que prefieras para tu programa.
    - lcpprest: Vincula el programa con la biblioteca libcpprest.
    - lboost_system: Vincula el programa con la biblioteca Boost.System, que es una de las dependencias de libcpprest.
    - lssl -lcrypto: Vincula el programa con las bibliotecas OpenSSL, que son necesarias para el soporte de HTTPS y otras características de seguridad.

- *Ejecutarlo*
    _./productsapp_

- *Consumirlo*
    _curl "http://localhost:5000?id=200"_
    