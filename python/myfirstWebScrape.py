import requests
from csv import writer
from bs4 import BeautifulSoup
import pandas as pd
from selenium import webdriver
from webdriver_manager.chrome import ChromeDriverManager

response = requests.get('https://www.newegg.com/p/pl?d=ssd')
products = []
prices = []
soup = BeautifulSoup(response.text, "html.parser")

posts = soup.find_all(class_ = 'item-container')

for a in soup.findAll(class_ = 'item-container'):
    name = a.find(class_ = 'item-title')
    price = a.find(class_ = 'price-current')
    products.append(name.text)
    prices.append(price.text.replace(' ',''))


df = pd.DataFrame({'Product Name': products, 'Product Price': prices})
df.to_csv('products.csv', index = False, encoding = 'utf-8')