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

- Habilitar el servicio Jenkis

```sudo systemctl enable jenkins```

 - Iniciar el servicio de jenkis

```sudo systemctl start jenkins ```

- Para verificar el status

```sudo systemctl status jenkins```

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

En gihut ir a Settings -> Webhooks y en PayloadUrl poner:
la url de ngrok o la de EC2.

http://3.145.92.103:8080/github-webhook

```
Ejecutar el build manual la primera vez,en caso tal que no se active el webHooks.

- Crea un tunel público usando ngrok

[Link ngrok](https://ngrok.com/)

- Iniciar ngrok
Agregar el token de auth. Ver en la página

```ngrok http http://localhost:8080```


### Ejemplo Jenkis en EC2

1. Crear una EC2 y aisgnar un nombre como: _JenkisServer_
2. Seleccionar la AMI. _Ubuntu Server 22.04 Free tier_
3. Instace type: _t2.micro Free tier_
4. Seleccionar o crear Key pair.
5. Create security group: _Allow SSH anywhere, allow Https, htpp from internet_
6. Configure storage: _default 8 Gb gp2_
7. Advance details: _Select the instance profile_ or create a new one
8. Habilitar el puerto 8080 
    - Seleccionar la instancia
    - Ir a Security
    - Seleccionar el Security groups wizard
    - Seleccionarlo y Click en Inboud rules
    - Edit inbound rules 
    - Add rule
    - Custom TCP - 8080 - Anywhere
    - Save rules
9. Launch Instance
    

#### Instalar jenkis

- Connect _EC2 Instance conenct _ o via SSH.
- Install Jenkis
[Instalación Ubuntu](https://pkg.origin.jenkins.io/debian-stable/)

```   
  sudo wget -O /usr/share/keyrings/jenkins-keyring.asc \
    https://pkg.jenkins.io/debian-stable/jenkins.io-2023.key
  
Then add a Jenkins apt repository entry:
    
  echo deb [signed-by=/usr/share/keyrings/jenkins-keyring.asc] \
    https://pkg.jenkins.io/debian-stable binary/ | sudo tee \
    /etc/apt/sources.list.d/jenkins.list > /dev/null
  
Update your local package index, then finally install Jenkins:

   
  sudo apt-get update
  sudo apt-get install fontconfig openjdk-17-jre
  sudo apt-get install jenkins```  

- Correr el servicio de Jenkis
 journalctl -u jenkins.service

- Verificar jenkis 
 ```https://ec2instance.ip:8080```

 Si hay algún error con https(puede ser SSL de Jenkis), intentar con 

 http://3.145.92.103:8080/

- Ver La clave

```sudo cat /var/lib/jenkins/secrets/initialAdminPassword```

 - Instalar los pluguins recomendados.

- 






