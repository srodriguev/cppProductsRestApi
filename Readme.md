### C++ Simple Rest API

- Make sure you have a IDE like vSCode

- *Instalar todas las depdendencias necesarias. como g++ (compilador c++) librerias web libboost-all-dev cpprest es una libreria para REST Api* esta instalación es recomendable tenerla en el ambiente.
    
    ```sudo apt update```

    ```sudo apt install -y git g++ libboost-all-dev libssl-dev libcpprest-dev libgtest-dev```

- *Para verificarla*

    ```dpkg -l | grep libcpprest```

- Clonar el projecto:

 ```git clone https://github.com/jhonarias91/cppProductsRestApi.git```

- Dar permisos a la carpeta 

```sudo chmod -R 777 cppProductsRestApi```

- *Compilar el programa*

    En la carpeta src:
    
    ```g++ -std=c++11 -o productsapp  main.cpp functions.cpp -lcpprest -lboost_system -lssl -lcrypto```


    - std=c++11: Especifica el estándar de C++ a usar, necesario para algunas características de C++ usadas con libcpprest.
      main.cpp: El nombre del source.cpp
    - o productsapp: Especifica el nombre del archivo de salida ejecutable. Puedes cambiar my_service por cualquier otro nombre que prefieras para tu programa.
    - lcpprest: Vincula el programa con la biblioteca libcpprest.
    - lboost_system: Vincula el programa con la biblioteca Boost.System, que es una de las dependencias de libcpprest.
    - lssl -lcrypto: Vincula el programa con las bibliotecas OpenSSL, que son necesarias para el soporte de HTTPS y otras características de seguridad.
    - functions.cpp es la implementación que se incluye en el main

- *Ejecutarlo*
    ```./productsapp```

- *Consumirlo*
    ```curl "http://localhost:5000?id=200"```

#### Testing

- Bajar el paquete de  gtest  
```sudo apt install -y libgtest-dev``` 
    Para fedora:
    ```sudo dnf install googletest-devel```

- Compilar las unitTest

```g++ -std=c++11 -o runUnitTest unitTest.cpp functions.cpp -lgtest -lgtest_main -lpthread -lcpprest -lboost_system -lssl -lcrypto```

- Ejecutar las unitTest
 
 ```./runUnitTest```


### Jenkis Pipeline

- Install Jenkis

    [Install Guide](https://pkg.jenkins.io/debian-stable)

- Instalar el plugin de Github

- Configurar el Pipeline

En build Trigger seleccionar: 

- [x] GitHub hook trigger for GITScm polling


```Groovy
pipeline {
    agent any
    stages{
        stage("Hook"){
            steps {
                git url: "https://github.com/jhonarias91/cppProductsRestApi"
            }
        }
        stage("Build"){
            steps {            
                sh "g++ -std=c++11 -o productsapp ./src/main.cpp ./src/functions.cpp -lcpprest -lboost_system -lssl -lcrypto"
            }
        }
        stage("Run"){
            steps{
                sh "chmod +x ./productsapp"
                sh "./productsapp"
            }
        }
    }
}
```
Ejecutar el build manual la primera vez,en caso tal que no se active el webHooks.

- Crea un tunel público usando ngrok

[Link ngrok](https://ngrok.com/)

- Iniciar ngrok
Agregar el token de auth. Ver en la página

```ngrok http http://localhost:8080```



