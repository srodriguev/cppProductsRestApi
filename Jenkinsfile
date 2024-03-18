pipeline {
    agent any
    environment {
        // Definimos variables de entorno
        //El nombre debe coincidir con el repositorio, o agregarle el tag con docker
        DOCKER_IMAGE = 'jhonarias91/productsapirepo:v0.0.${BUILD_NUMBER}' 
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
                // Build local
                sh "g++ -std=c++11 -o productsapp ./src/main.cpp ./src/functions.cpp -lcpprest -lboost_system -lssl -lcrypto"
            }
        }  
        stage("UnitTest")  {
            steps {
                    sh "g++ -std=c++11 -o unittest ./src/unitTest.cpp ./src/functions.cpp -lcpprest -lboost_system -lssl -lcrypto"
                    sh "./unittest"
                }
            }        
        stage("Dockerize") {
            steps {
                script {
                    // Se crea la imágen para el Docker
                    sh "docker build -t ${DOCKER_IMAGE} ."                    
                }
            }
        }
        stage('Login Push Docker Image') {
            steps {
                script {
                    // Usar credenciales de Jenkins para login en Docker Hub
                    withCredentials([usernamePassword(credentialsId: 'docker_hub_credentials_id', passwordVariable: 'DOCKER_HUB_PASSWORD', usernameVariable: 'DOCKER_HUB_USER')]) {
                        sh "echo $DOCKER_HUB_PASSWORD | docker login --username $DOCKER_HUB_USER --password-stdin"
                    }
                    // Opcional: Publicar en un registro de Docker
                    sh "docker push ${DOCKER_IMAGE}"
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
