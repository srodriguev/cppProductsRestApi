### C++ Simple Rest API

1. ### Sources


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

2. ### Testing

- Bajar el paquete de  gtest  
```sudo apt install -y libgtest-dev``` 
    Para fedora:
    ```sudo dnf install googletest-devel```

- Compilar las unitTest

```g++ -std=c++11 -o runUnitTest unitTest.cpp functions.cpp -lgtest -lgtest_main -lpthread -lcpprest -lboost_system -lssl -lcrypto```

- Ejecutar las unitTest
 
 ```./runUnitTest```


3. ### Jenkis Pipeline (solo para ssh _deprecated_)

- Install Jenkis

    [Install Guide](https://pkg.jenkins.io/debian-stable)

- Habilitar el servicio Jenkis

```sudo systemctl enable jenkins```

 - Iniciar el servicio de jenkis

```sudo systemctl start jenkins ```

- Para verificar el status

```sudo systemctl status jenkins```

- Instalar el plugin de Github

- Instalar pluguing SSH Pipeline Steps Version 2.0.68.va_d21a_12a_6476  o superior

- Conectarse a la EC2, ir a /opt y dar permisos (si se va a desplegar a /opt)

- Agregar la ip de EC2  known host

- ssh-keyscan -t rsa 3.138.34.44 

- copiar el contenido en un archivo known_host y copiar ese archivo 


 en alguna ruta como /var/lib/jenkins/workspace

darle permisos de lectura a jenkis sobre ese archivo .
en la parte de knownHostsFile del sshCommand agregar esa ruta.



 ```chmod -R 777 .```

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


4. ### Jenkis en EC2

1. Crear una EC2 y aisgnar un nombre como: _JenkisServer_
2. Seleccionar la AMI. _Ubuntu Server 22.04 Free tier_
3. Instace type: _t2.midle_
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
    - Custom TCP - 5000 - Anywhere
    - SSH - 22 - Anywhere
    - Save rules
9. Launch Instance
    

5. ### Instalar jenkis

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

  ```sh 
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
 - Instalar el GitHub Plugin para los webhooks
 - test webhook


#### Create el Pipeline.

- Agregar un nuevo item y seleccionar Pipeline
- asiganr un nombre: webHookDocker
- *Build Triggers*: GitHub hook trigger for GITScm polling
- *Pipeline*: Pipeline Script from SCM.
- SCM: Git 
    - Repository URL: https://github.com/jhonarias91/cppProductsRestApi
- Branch: */master
- Script Path: Jenkinsfile
- Save

### Docker deploy

- Instalar docker
    - sudo apt-get update: Actualiza lista de paquetes disponibles.
    - sudo apt-get install -y apt-transport-https ca-certificates curl software-properties-common: Instala utilidades esenciales para añadir repositorios HTTPS.
    - curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -: Añade clave GPG de Docker.
    - sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable": Añade repositorio de Docker.
    - sudo apt-get update: Actualiza lista de paquetes nuevamente.
    - sudo apt-get install -y docker-ce: Instala Docker Community Edition.
    - sudo systemctl start docker: Inicia el servicio de Docker.
    - sudo systemctl enable docker: Habilita Docker al arranque.
    - sudo usermod -aG docker ${USER}: Añade usuario al grupo Docker.

 ```sudo apt-get update
sudo apt-get install -y apt-transport-https ca-certificates curl software-properties-common
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
sudo apt-get update
sudo apt-get install -y docker-ce
sudo systemctl start docker
sudo systemctl enable docker
sudo usermod -aG docker ${USER}
```


  - Agregar el usuario de jenkis al grupo docker para poderle dar 
  permisos al usuario jenkis ejecutar comandos docker sin sudo.
    
    ```sudo usermod -aG docker jenkins``` 

- Verificamos que el puerto no esté ocupado

  ```lsof -i :5000```
  
  - Jenkis pipeline

  ```Groovy
  pipeline {
    agent any
    environment {
        // Define tus variables de entorno aquí
        DOCKER_IMAGE = 'productsapi_0.0.1:dev'
        DOCKER_CONTAINER_NAME = 'productsapicontainer'
    }
    stages {
        stage("Checkout") {
            steps {
                // Clona tu código fuente
                git url: "https://github.com/jhonarias91/cppProductsRestApi"
            }
        }
        stage("Build") {
            steps {
                // Compila tu aplicación si es necesario
                sh "g++ -std=c++11 -o productsapp ./src/main.cpp ./src/functions.cpp -lcpprest -lboost_system -lssl -lcrypto"
            }
        }
        stage("Dockerize") {
            steps {
                script {
                    // Construir la imagen Docker
                    sh "docker build -t ${DOCKER_IMAGE} ."
                    // Opcional: Publicar en un registro de Docker se debe autenticar
                    // sh "docker push ${DOCKER_IMAGE}"
                }
            }
        }
        stage("LocalDeploy") {
            steps {
                script {                    
                    // Detener y eliminar el contenedor si ya está en ejecución (opcional)
                    sh "docker stop ${DOCKER_CONTAINER_NAME} || true && docker rm ${DOCKER_CONTAINER_NAME} || true"
                    
                    // Ejecutar el contenedor
                    sh "docker run -d --name ${DOCKER_CONTAINER_NAME} -p 5000:5000 ${DOCKER_IMAGE}"
                }
            }
        }
    }
}
  ```

*Consumirlo desde el host local*

    ```http://localhost:5000?id=200```

    ### Despliegue en EC2.

    #### Configurar EC2 Instance

     Vamos a necesitar una instance type t2.medium ya que nos ofrece 2 vCPUs y 4 GB de memoria que es lo que vamos a necesitar 
     para tener Jenkis, docker y correr el servicio.





### Docker Image

- Agregar la SSH a las credenciales de Jenkis 
usando private key en username poner el de la ec2: ubuntu 
y asignar un id o dejar que lo genere (1540cfc2-b32f-48a6-820c-54e3a9ab0c95)






