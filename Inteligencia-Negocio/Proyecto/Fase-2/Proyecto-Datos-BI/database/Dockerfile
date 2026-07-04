# Usamos la imagen de Java que sí funcionó perfectamente
FROM eclipse-temurin:8-jre-focal

# Instalamos unzip por si acaso se necesita internamente
RUN apt-get update && apt-get install -y unzip && rm -rf /var/lib/apt/lists/*

# Definimos el directorio de trabajo dentro del contenedor
WORKDIR /opt/data-integration

# Le damos permisos de ejecución a los archivos cuando Docker los monte
CMD ["chmod", "+x", "/opt/data-integration/kitchen.sh"]