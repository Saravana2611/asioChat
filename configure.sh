rm -rf build/ cert/

mkdir cert
cd cert

openssl genrsa -out ca.key 2048
openssl req -x509 -new -key ca.key -out ca.pem -subj "/CN=Test CA"

openssl genrsa -out server.key 2048
openssl req -new -key server.key -out server.csr -subj "/CN=127.0.0.1"
openssl x509 -req -in server.csr -CA ca.pem -CAkey ca.key -out server.pem

openssl genrsa -out client.key 2048
openssl req -new -key client.key -out client.csr -subj "/CN=client"
openssl x509 -req -in client.csr -CA ca.pem -CAkey ca.key -out client.pem

cd ..

echo "build/ directory removed"
cmake -S . -B build/
