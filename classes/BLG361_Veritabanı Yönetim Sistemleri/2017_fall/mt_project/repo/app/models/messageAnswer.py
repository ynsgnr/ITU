class MessageAnswer:
    def __init__(self, text=None, a_id=0, username='admin', messageId=0):
        self.id = a_id
        self.username = username
        self.messageId = messageId
        self.text = text
