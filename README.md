# Malware Project “Bypass antivirus with malware programming and forensics methodology”

**NOTE** : This repository is not completed

The purpose of this project is to bypass Windows Defender and create a backdoor with a Malware (executable file) using a phishing method attack. This github is a step-by-step for setting up the environment.
The primary objective of this project is to bypass Windows Defender and develop a stealthy backdoor by leveraging a Malware (executable file) through a phishing attack method. This GitHub repository serves as a comprehensive guide, providing step-by-step instructions on how we successfully bypassed Windows Defender.


## Table of Contents:

   - [Principle of attack](#principle-of-attack)
   - [Phishing part](#phishing-part)
      - [AWS](#aws)
      - [Mailjet](#mailjet)
      - [Domain name](#domain-name)
      - [Evilgophish](#evilgophish)
           - [Gophish](#gophish)
           - [Evilginx2](#evilginx2)
      - [Apache](#apache)
      - [Phishing campaign](#phishing-campaign)
      - [Demo](#demo)
   - [Malware part](#malware-part)


## Principle of attack

![image](https://user-images.githubusercontent.com/80312634/227156955-5988f20d-ddf4-4cf4-8a12-cfc88e23ab5f.png)




## Phishing part

### AWS
---

We will use [AWS service](https://aws.amazon.com/) to create a virtual machine and install all the servers for phishing inside.
 
After login to your account, search for `EC2 service` and launch a `Ubuntu server` instance with `t2.micro` as instance type.

You must also generate a key pair to connect remotly to your AWS instance using SSH protocol. It will be needed later.
 
 
### Mailjet
---

Mailjet is a service for email delivery. Our phishing email link will go through our domain then mailjet to be received by our potential victims.

You will have to configure your DNS records by adding a SPF TXT record and TXT record. If you did, everything should be green.

![image](https://user-images.githubusercontent.com/80312634/227162792-3b111c2f-cf8d-4603-8ea2-95a2eb021efe.png)

You also have to verify your domain name.

![image](https://user-images.githubusercontent.com/80312634/228022183-9362bcf0-6291-4dea-868f-65a9cbfd4cf1.png)

There we go, mailjet is set up.

![image](https://user-images.githubusercontent.com/80312634/227162836-439494b4-1cb0-486b-a1f2-d00400b33989.png)




### Domain name
---

The domain is used to attract the victim to the apache web service to steal his/her credentials.

For this project, we choose Ionos for our web hosting company. But we can choose the one you prefer.

In your DNS records, you will have to create records as shown below:

![image](https://user-images.githubusercontent.com/80312634/228021532-f78b87fe-6b69-4667-bb85-6654d0da76e5.png)



| Number of Records | Type | Usage                       |
| ------------------|:----:| ---------------------------:|
| 5                 | A    | with AWS public ip    |
| 3                 | TXT  | for Mailjet                 |
| 1                 | TXT  | for evilgophish certificate |

> Be careful, AWS ip can change if you restart your instance 

> Also, for mailjet, one is a SPF TXT record and the other two are normal TXT records


### Evilgophish
---

`Evilgophish` is the combination of evilginx2 and gophish.

You can download the repository in your AWS instance with the command below:

```
git clone https://github.com/fin3ss3g0d/evilgophish
```

Now that you clone it, on your AWS instance's terminal, you must first setup the configuration of `evilgophish`.
      
```
sudo ./setup.sh <your_domain_name> login,www true <url_redirection> true client_id false
```

`<url_redirection>` : URL to redirect unauthorized Apache requests. In our case, we redirect unauthorized requests to `esme.fr`

Then, you will have to copy the lets encrypt command displayed by `setup.sh` that starts with:

```
sudo cerbot ...to... <your_domain_name>' 
```      
      
It will create an `_acme_challenge` certificate that you will have to paste it in your DNS as TXT record. 

---

   - ### Gophish

Now that Evilginx2 setup is configured, we can launch `gophish`. Go to `gophish` folder and run the command.

```
sudo ./gophish
```

A password and a login are displayed to access to gophish logging page.

Then to access the evilgophish dashboard, we must enter the following command with a terminal other than AWS.

```
ssh -L 3333:127.0.0.1:3333 -i <private_key_file_to_access_AWS> <user>:<AWS_public_ip>
```

`<user>` should be `ubuntu` if you create a ubuntu instance on AWS.

You can now access Gophish page at this IP address:

```
https://127.0.0.1:3333
```

---

   - ### Evilginx2

Let's also launch `evilginx2` to create our phishlets. Go to evilginx2 folder.

```
sudo ./evilginx2 -g <path_to_gophish>.gophish.db
```

You, first, need to configure your domain name and IP address with the following commands:  

```
Config domain <domain_name>

Config ip <AWS_public_ip>
```

Once done, we can then set up the phishlet we want to use.

```
phishlets hostname <phishlet_name> <domain_name>

phishlets enable <phishlet_name>
```

You can type `phishlets` to verify the status and active phishlets.

You should have choose a phishlet and enable it by the time. The last step is to create phishing link that we will send to our victim to carry out our attack:  

```
lures create <phishlet_name>  

lures get-url <id>
```


Don't forget to delete your lures and desactivate your phishlet before shutting down your instance.

```
lures delete all

phishlets disable <phishlet_name>
```


### Apache
---

`Apache2` is used as a proxy to the local `evilginx2` server and an additional hardening layer for your phishing infrastructure.

```
sudo apt update

sudo apt install apache2
```

### Phishing campaign
---

Create a User/Group for the victim's email

![image](https://user-images.githubusercontent.com/80312634/227782709-6e4c4ddc-335c-424e-acad-b8a6b7f1ad19.png)

Then you have to create a sending profile with the smtp 

![image](https://user-images.githubusercontent.com/80312634/228037070-b9601fa1-2fa1-4ca8-98b9-09c5d1b867b3.png)

You can find the smtp server, username and password in mailjet.

>The username is your api.
>The password is your secret key.

![image](https://user-images.githubusercontent.com/80312634/228024329-a3584747-3f4c-4395-9779-c3d1c135aa82.png)

Next time is email creation and then you can launch a campaign.

![image](https://user-images.githubusercontent.com/80312634/228037155-339f8294-37a5-43ee-b936-3cab17682039.png)

### Demo
---

VIDEO

## Malware part

We need to install multiples tools in Windows Virtual Machine:


- Since executing C++ code can damage our computer, we installed a [windows virtual machine](https://developer.microsoft.com/en-us/windows/downloads/virtual-machines/).
        
- To execute C++ code, we have to install a compiler, we used [mingw64](https://code.visualstudio.com/docs/cpp/config-mingw) gcc for Virtual Studio Code IDE to perform this task.
          
- Install [Pebear](https://github.com/hasherezade/pe-bear)

- Install [procmon](https://learn.microsoft.com/en-us/sysinternals/downloads/procmon)

- Install [commando](https://github.com/mandiant/commando-vm)

- Install [ressourcehacker](http://www.angusj.com/resourcehacker/)

- MsfVenom is a usefull tool to generate payload. At first, we tried to generate a calculator with this command:

```
msfvenom --platform windows -- arch x64 -p windows/x64/exec CMD = calc.exe -b \x00\x0A\x0D  -f c
```

