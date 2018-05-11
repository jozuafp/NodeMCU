# relay nodemcu 
- Control Relay with NodeMCU ESP8266 WiFi


# Git notes

## Edit files locally

* `git add . -A` stage changes
* `git commit -m 'message'` commit the staged changes
* `git push -u origin master` synchronize server repository to our local

## Files was edited remotely

* If there is changes in local repository, you have to commit first by using `git add . -A && git commit -m 'message'`
* `git pull origin master` syncrhonize our local repository to server's
* If file was edited locally before `pull`, then we have to commit and push
    ```bash
    git add . -A
    git commit -m 'message'
    git push -u origin master
    ```

