#requires selenium and google driver
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import Select
from selenium.common.exceptions import NoSuchElementException

import csv
import time

username_id = "ContentPlaceHolder1_tbUserName"
password_id = "ContentPlaceHolder1_tbPassword"
dismiss_announcement_id = "Button1"
sis_password_name = "PIN"

initial_csv_path="grade_distrubitions/"

link_class_name = "submenulinktext2"
#first page:
student_service_index = -2
personal_information_index = -1
#student service page:
registration_index = -4
student_records_index = -3
advisor_menu_index = -2
grade_distrubition_index = -1
#grade distrubition page:
term_selector_name ="term"
class_selector_name = "crn"
selector_tag = "select"
table_class = "table1"

sleep_time_small = 0
sleep_time = 0

request_count = 0

def run():
    global request_count
    driver = webdriver.Chrome()
    config = get_config("web_driver_config.txt")
    driver.get("http://uzay.sis.itu.edu.tr/login/index.php")

    login(driver,config[0],config[1])
    time.sleep(sleep_time_small)
    login_sis(driver,config[2])
    time.sleep(sleep_time_small)

    first_page_elements = driver.find_elements_by_class_name(link_class_name)
    first_page_elements[student_service_index].click()
    check_for_load_fail(driver)
    request_count+=1
    time.sleep(sleep_time_small)
    second_page_elements = driver.find_elements_by_class_name(link_class_name)
    second_page_elements[grade_distrubition_index].click()
    check_for_load_fail(driver)
    request_count+=1

    grade_distrubitions = itarate_selectors(driver,parse_data_from_table)

    #write to files:
    for classes in grade_distrubitions:
        try:
            writer = csv.writer(open(initial_csv_path+slugify(classes[0])+'.txt', 'w',encoding='utf-8'))
            for row in classes[1:len(classes)]:            
                writer.writerow(row)
        except:
            print("File for "+classes[0]+" exists")
    driver.close()

def check_for_load_fail(driver):
    for entry in driver.get_log('browser'):
        print(entry)

def slugify(value):
    import unicodedata
    import re
    #Taken from django project by https://stackoverflow.com/questions/295135/turn-a-string-into-a-valid-filename
    """
    Normalizes string, converts to lowercase, removes non-alpha characters,
    and converts spaces to hyphens.
    """
    value = value.replace("\n","")
    value = str(unicodedata.normalize('NFKD', value).encode('ascii', 'ignore'))
    value = str(re.sub('[^\w\s-]', '', value).strip().lower())
    value = str(re.sub('[-\s]+', '-', value))
    return value[1:] #adds b to the begining i dont know wht

def itarate_selectors(driver,function):
    global request_count
    time.sleep(sleep_time)
    check_for_load_fail(driver)
    selector_option_lenght = len(Select(driver.find_element_by_tag_name(selector_tag)).options)
    return_values = list()
    for index in range (0,selector_option_lenght):
        #after each back command element gets detached, so find it again
        selector_element = driver.find_element_by_tag_name(selector_tag)
        selector = Select(selector_element)
        selector.select_by_index(index)
        selector_element.submit()
        request_count+=1
        print("Request_count: "+str(request_count))
        try:
            driver.find_element_by_css_selector(selector_tag)
            return_values+=itarate_selectors(driver,function)
        except NoSuchElementException:
            return_values+=[function(driver)]
        time.sleep(sleep_time)
        check_for_load_fail(driver)
        driver.execute_script("window.history.go(-1)") # go back
        time.sleep(sleep_time)
        check_for_load_fail(driver)
    return return_values

def parse_data_from_table(driver):
    table = get_table(driver)
    data = list()
    data.append(get_title(driver))
    for row in table.find_elements_by_tag_name("tr"):
        data.append([item.text for item in row.find_elements_by_tag_name("td")])
    return data

def get_table(driver):
    return driver.find_element_by_class_name(table_class)

def get_title(driver):
    return driver.find_element_by_tag_name("b").text


def login(driver,username,password):
    username_input = driver.find_element_by_id(username_id)
    username_input.send_keys(username)
    password_input = driver.find_element_by_id(password_id)
    password_input.send_keys(password)
    check_for_load_fail(driver)
    time.sleep(1)
    try:
        dismiss_button = driver.find_element_by_id(dismiss_announcement_id)
        dismiss_button.click()
        print("Dissmising Announcement")
    except:
        return

def login_sis(driver,password):
    password_input = driver.find_element_by_name(sis_password_name)
    password_input.send_keys(password)
    password_input.send_keys(Keys.ENTER)
    check_for_load_fail(driver)

def get_config(filename):
    username = ""
    password = ""
    sis_password = ""
    try:
        f = open(filename, "r")
        username = f.readline()
        password = f.readline()
        sis_password = f.readline()
    except:
        print("Are you sure config file ("+filename+") exists and configured with username, password and sis_password at each line?")
    return username,password,sis_password

run()