try{if(Get-Command python)}
catch{
    try{if(Get-Command scoop)}catch{iex (new-object net.webclient).downloadstring('https://get.scoop.sh')}
    scoop install python
}
pip install selenium
try{if(Get-Command chromedriver)}
catch{
    scoop install chromedriver
}
python get_grad_dist.py