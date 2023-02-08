import hashlib


# hash密码
def HashPassword(password):
    salt = "48818659-2BBF-44B9-8865-5C3545392364"
    txt = password + salt
    h = hashlib.md5(txt).hexdigest()
    return h