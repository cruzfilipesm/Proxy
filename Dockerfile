# Usar uma imagem mínima baseada no Ubuntu 24.04
FROM ubuntu:24.04 AS runner

# Instalar apenas as bibliotecas runtime necessárias
RUN apt-get update && apt-get install -y --no-install-recommends \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

# Criar diretório de execução
WORKDIR /app

# Copiar o binário pré-compilado
COPY cmake-build-release/Proxy /app/Proxy

# Definir ponto de entrada
CMD ["/app/Proxy"]
