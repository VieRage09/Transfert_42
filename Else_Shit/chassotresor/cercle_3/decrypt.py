import bcrypt
from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad
import base64

def derive_key(password: str, salt: bytes, key_length: int = 32) -> bytes:
    return bcrypt.kdf(
        password=password.encode(),
        salt=salt,
        desired_key_bytes=key_length,
        rounds=12
    )

def decrypt_bfe_string(bfe_string: str, password: str) -> str:
    try:
        data = base64.b64decode(bfe_string)
        salt = data[:16]
        iv = data[16:32]
        ciphertext = data[32:]

        key = derive_key(password, salt)

        cipher = AES.new(key, AES.MODE_CBC, iv)
        decrypted = cipher.decrypt(ciphertext)
        plaintext = unpad(decrypted, AES.block_size)
        return plaintext.decode("utf-8")
    except Exception as e:
        return f"[ERREUR] {str(e)}"

# Données BFE
bfe_strings = [
    "VAAe8ElCrUAbXivz0ueiIpv/u/ia9PL50+HI+8/bgPKLESHlptPLpu0PW9zWV/LwDVaOqCRCGu6Gopk1X0i6Kn7t",
    "VADYjxBiOQSAWNqB652klCj13URaziELdHd+2Z38XCMD9dvO9tSyFob6Il3NBX9YXrgZEiQK7JZJ7w5t0N80wMl7"
]

passwords = ["Tesla", "Nikola Tesla"]

# Tester tous les couples
for bfe in bfe_strings:
    print(f"🔐 Donnée BFE : {bfe}")
    for pwd in passwords:
        print(f"Mot de passe : {pwd}")
        result = decrypt_bfe_string(bfe, pwd)
        print("➡️ Résultat :", result)
        print("-" * 60)
