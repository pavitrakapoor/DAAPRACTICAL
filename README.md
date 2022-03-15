##Python Developer Assignment
#Approach
So there was 3 different level of webpages.
1. Main A-Z Content List
2. Specific Case Sensitive Alphabet Content List
3. Main Topic Page

3 different functions are used in the code to scrape each level and then each function would call the function responsible for next level.
For first level function scrape(), it would scrape the all the links and after scraping each link it would call the second level function mainscrape() which then would scrape again for numerous weblinks. Same way after scraping each link it would call the third level function contentscraper() which would scrape the content table out of it and append it to a dataframe.
The program would take a input n from user as in how many sites they want to scrape. Once the iterator is greater than n, the function would break and data will be saved as a csv file.
As I was not familiar with Mongodb and had an emergency at home due to which there was lack of time, So I tried to save the data locally in csv file.
The code can be reused for similar type of websites just by changing the website in code.

#Possible Future Improvements
We can take the similar websites as input too from the users which would make it more efficient and reusable.
We can save the data in mongodb.
We can find more efficient way of doing the same thing.
