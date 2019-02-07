# ITU CS Archive
  ITU Computer Science Student's archive for classes, homeworks, lecture notes and more...

## File Structure

 Folder names separated with "_".

   - ### Root
     Root file has classes folder, files apply to whole department (such as prerequisite classes diagram), grade distrubition folder, internships folder and projects folder
    
   - ### Classes Folder
     Class folders named with class code then class names. In class folders you can find class files by year. Contributions to increase covered terms are welcome. 
     Class files grouped as homeworks, lecture notes (can be slides or student notes) and projects. You can related files under those folders.
    
   - ### Grade Distrubition Folder
     This folder has grade distrubitions per class. Each file named with term, class code, class teacher in snake case. If there is an unknown variable it is referenced as 'unknown'.
    
   - ### Internships Folder
     This folder has internship reports prepared by students. Files named with internship term, company name, subject and student name.

   - ### Projects Folder
      This folder has project files prepared by students. Each folder named with term, subject, student name and professor's name.

## Automaticly Saving Grade Distrubitions
 You can use ```get_grad_dist.py``` code to automaticly extract grade distrubitions and saved them under grade distrubitions folder as csv file.

  - ### Requirements
    Chrome, Python, selenium and chromedriver is required. To install python refer to  [python website](https://www.python.org/), for selenium please refer to [selenium website](https://www.seleniumhq.org/), you can also find information about chromedriver here.

    - #### Automated Install and Run (Untested)
      Windows only: You can double click on ```get_grad_dist.ps1``` to install dependencies and run automaticly, requires chrome.

  - ### Configuring and Running
    - Crate file with the same format as ```web_driver_config_example.txt```, or edit this file with your ninova username and password, and your sis password (the password you enter after logging in to sis). 
    - Save your configuration as ```web_driver_config.txt```
    - Open a console, go the this reposities location and run ```py get_grad_dist.py``` or ```python get_grad_dist.py```
    - If you have any problems check configuration, and you still have any problems it might be because sis blocked you, (they love blocking people). Wait a couple minutes then run program again

  - ### Sending Files to this repo
    - After extracting grades you can use ```git push``` to add extracted grades to this repo so anyone can see them