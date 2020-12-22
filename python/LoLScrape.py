import requests
from csv import writer
from bs4 import BeautifulSoup
import pandas as pd
from selenium import webdriver
from webdriver_manager.chrome import ChromeDriverManager

username = input("enter username: ")
response = requests.get('https://na.op.gg/summoner/userName='+username)


champions = []
kills = []
deaths = []
assists = []
gameResults = []
KDAs = []
soup = BeautifulSoup(response.text, "html.parser")

posts = soup.find_all(class_ = 'GameItemWrap')


for a in soup.findAll(class_ = 'GameItemWrap'):
    champion = a.find(class_ = 'ChampionName')
    kill = a.find(class_ = 'Kill')
    death = a.find(class_ = 'Death')
    assist = a.find(class_ = 'Assist')
    gameResult = a.find(class_ = 'GameResult')
    kda = a.find(class_ = 'KDARatio')
    champions.append(champion.a.text)
    kills.append(kill.text)
    deaths.append(death.text)
    assists.append(assist.text)
    gameResults.append(gameResult.text.replace('\t','').replace('\n',''))
    KDAs.append(kda.text.replace('\t','').replace('\n',''))
    


df = pd.DataFrame({'Champions': champions, 'Kills': kills, 'Deaths': deaths, 'Assists': assists , 'Victory/Defeat': gameResults, 'KDAs': KDAs})
df.to_csv('LeaugeData.csv', index = False, encoding = 'utf-8')