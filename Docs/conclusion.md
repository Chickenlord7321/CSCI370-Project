# Conclusion

- Author: Caleb Bronn
- Student number: 658349659
- Last update: 13 Apr 2025

## Development Process

I had a lot of issues with my project and had to downscale considerably. I talked with Merlin about it, we're not exactly sure what the issue is, but Otter is very limited in what it is able to compile. I had to abandon my initial idea of making API requests for users to add new movies to the database since all the HTTP request libraries I tried were header-only and were unable to compile. Otter complains about "Virtual Memory exhausted. Cannot allocate memory". Trust me, I tried three different libraries, none of them will compile. 

Also, I wanted to include regex for checking the passwords and usernames, but regex will not compile either (gives the same virtual memory error as the HTTP libraries). I find that error even more strange since I have used regex before in Assignments 7 and 8, but for some reason it won't compile in my project. So I had to abandon that as well.

I ran out of time and did not complete *all* the ideas I had for ways that users could search for movies and reviews, such as searching by score, or viewing only movies that were released recently. However, I think the app is functional and pretty fun to use. It's possible to search both movies and reviews by a search term, which works very well and is pretty adaptable to whatever the user is looking for. The search feature applies to the review text and movie overviews as well as the titles, so even if you don't know the title of a movie/review, you can still find it.

On the topic of downscaling my project, I had originally intended to use the [Crow Web App framework](https://crowcpp.org/master/) to create a web server, but I wasn't able to get it to compile on Otter either. That's kinda the theme of this project! So instead I've just written the results to html files in the Output directory, which can be copied over to your own machine and viewed in any web browser.

## Future Work

Given the limitations of Otter, there's not much that can be done to improve on the project or bring it closer to my original idea. However, it would be nice to add string parsing to check user password and username to ensure they only contain valid characters (A-Z, 0-9, or any of !@#$%^&*).

It's also possible to add more search features that allow users to view different types of lists. For example, a list of recently released movies.
