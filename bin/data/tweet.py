#!/usr/bin/env python
# coding: UTF-8

from requests_oauthlib import OAuth1Session
import json
import time
import sys


### Constants
oath_key_dict = {
    "consumer_key": "LIcSrKvkEtD9fDd9AomTy9rIi",
    "consumer_secret": "rt0FRMIAjuij9UZrkaKO3Y7n6GntH5cPKgm1DAhR7fM9OciKHh",
    "access_token": "729535300855173120-aRxHdlRTFHtSEEBRziLJVl9egzv4cTn",
    "access_token_secret": "2ifH4LY5qtSNWxDFRf3O6NcZMsYLmPrKz1EX2VydErxwN"
}

### Functions

def main():
    f = open('tweet.txt', 'w') #open file
    old_tweets = -1
    while 1:
        tweets = tweet_search( u"#母の日", oath_key_dict)
        
        for tweet in tweets["statuses"]:
            tweet_id = tweet[u'id_str']
            text = tweet[u'text']
            created_at = tweet[u'created_at']
            user_id = tweet[u'user'][u'id_str']
            user_description = tweet[u'user'][u'description']
            screen_name = tweet[u'user'][u'screen_name']
            user_name = tweet[u'user'][u'name']
            
            if old_tweets != tweet_id:
                # print "tweet_id:", tweet_id
                print "screen_name:", screen_name
                print "text:", text
                # print "created_at:", created_at
                # print "user_id:", user_id
                # print "user_desc:", user_description
                # print "user_name:", user_name
                old_tweets = tweet_id
                # write json file
                f.write( str(screen_name) + ",#&&\n" ) #user id
                f.write( text.encode('utf-8') + ",#&&\n" ) #post text
                f.flush()

        time.sleep(5)
        break

    return


def create_oath_session(oath_key_dict):
    oath = OAuth1Session(
                         oath_key_dict["consumer_key"],
                         oath_key_dict["consumer_secret"],
                         oath_key_dict["access_token"],
                         oath_key_dict["access_token_secret"]
                         )
    return oath

def tweet_search(search_word, oath_key_dict):
    url = "https://api.twitter.com/1.1/search/tweets.json?"
    params = {
        "q": unicode(search_word),
        "lang": "ja",
        "result_type": "recent",
        "count": "200" #get num
    }
    oath = create_oath_session(oath_key_dict)
    responce = oath.get(url, params = params)
    if responce.status_code != 200:
        print "Error code: %d" %(responce.status_code)
        return None
    tweets = json.loads(responce.text)
    return tweets


### Execute
if __name__ == "__main__":
    main()
print "END"


