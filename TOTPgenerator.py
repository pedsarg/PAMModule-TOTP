import hmac, base64, struct, hashlib, time, sys

secretKey = sys.stdin.readline().strip()

def get_hotp_token(secret, intervals_no):
    key = base64.b32decode(secret, True)
    msg = struct.pack(">Q", intervals_no)

    h = hmac.new(key, msg, hashlib.sha1).digest()
    o = o = h[19] & 15
    h = (struct.unpack(">I", h[o:o+4])[0] & 0x7fffffff) % 1000000

    return h

def get_totp_token(secret):

    x =str(get_hotp_token(secret,intervals_no=int(time.time())//30))

    while len(x)!=6:
        x+='0'
    return x

secret = secretKey
generatedCode = get_totp_token(secret)

with open("/root/key.txt", "w") as textfile:
    textfile.write(generatedCode)
