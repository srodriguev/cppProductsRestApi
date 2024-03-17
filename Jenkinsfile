pipeline {
    agent any
    environment {
        // Definimos variables de entorno
        DOCKER_IMAGE = 'productsapi_0.0.1:dev'
        DOCKER_CONTAINER_NAME = 'productsapicontainer'
    }
    stages {
        stage("Checkout") {
            steps {
                // CLonación del proyecto
                git url: "https://github.com/jhonarias91/cppProductsRestApi"
            }
        }
        stage("Build") {
            steps {
                // Hacemos un build para las pruebas locales
                sh "g++ -std=c++11 -o productsapp ./src/main.cpp ./src/functions.cpp -lcpprest -lboost_system -lssl -lcrypto"
            }
        }
        stage("Dockerize") {
            steps {
                script {
                    // Se crea la imágen para el Docker
                    sh "docker build -t ${DOCKER_IMAGE} ."
                    // Opcional: Publicar en un registro de Docker, se debe autenticar
                    // sh "docker push ${DOCKER_IMAGE}"
                }
            }
        }
        stage("Deploy-EC2") {
            steps {
                script {                    
                    // Se detiene y elimina el contenedor si ya está en ejecución
                    sh "docker stop ${DOCKER_CONTAINER_NAME} || true && docker rm ${DOCKER_CONTAINER_NAME} || true"
                    
                    // Se ejecuta el contenedor
                    sh "docker run -d --name ${DOCKER_CONTAINER_NAME} -p 5000:5000 ${DOCKER_IMAGE}"
                }
            }
        }
    }
}
