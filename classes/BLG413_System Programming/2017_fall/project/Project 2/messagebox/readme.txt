This module is a messagebox between users
In order to use it users must be added to the chat user group
install using sudo ./install.sh
Superuser permissions requeried for install!
send messages with echo and read with cat commands
those commands can run on /dev/messagebox
to specify user to send message use @<username> before typing message

Examples:
echo "@joe hello" > /dev/messagebox
cat /dev/messagebox
