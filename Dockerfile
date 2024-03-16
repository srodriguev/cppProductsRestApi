# Usar como base la imagen de Ubuntu
FROM ubuntu:latest

# Instalar dependencias
RUN apt-get update && apt-get install -y \
    g++ \
    libboost-all-dev \
    libssl-dev \
    libcpprest-dev \
    && rm -rf /var/lib/apt/lists/*

# Copiar los archivos del proyecto al contenedor
COPY . /app

# Establecer el directorio de trabajo
WORKDIR /app/src

# Compilar la aplicación
RUN g++ -std=c++11 -o productsapp main.cpp functions.cpp -lcpprest -lboost_system -lssl -lcrypto

# Exponer el puerto que usa tu aplicación
EXPOSE 5000

# darle permisos 
RUN chmod +x ./productsapp

# Comando para ejecutar la aplicación
CMD ["./productsapp"]
