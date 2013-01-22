Custom Drupal Modules by mwetmore
===============================

This GitHub repository contains some experimental modules which I am messing around with at the moment.  So of them are stable, some of them aren't
but feel free to touchbase with me on Twitter ([@mwetmore](http://twitter.com/mwetmore) and I'll let you know.  I'll also try and keep the entries below up to date so that you
know exactly what is going on.  Thanks!

Context Google Analytics
------------------------
The Drupal Context Module [(Link)](http://drupal.org/project/context) is a powerful module that allows you to easily modify the placement of Blocks, Menus, and
Styles based upon conditions which are defined.  The Context Google Analytics module creates the option for a number of conditions based upon values in
a users Google Analytics Cookie, once enabled the following conditions will be available:
- GA Campaign
- GA Source
- GA Medium
- GA Content
- GA Term
- GA Total Visits

This module source is for Drupal 7, I have a Drupal 6 version the works, and it requires that the following modules also be installed:
- Token (In D7 Core) [link](http://drupal.org/project/token)
- Context [link](http://drupal.org/project/context)
- Google Analytics  [link](http://drupal.org/project/google_analytics)
- Google Analytics Tokenizer [link](http://drupal.org/project/ga_tokenizer)

The conditions above to added to the Google Analytics token by search/media campaigns from Google, but you can create your own campaigns and place the page
parameters where you want, and watch the traffic in GA, and then hide blocks by campaigns, or remove/show menus, skys the limit.  More details on configuring 
Google Campaign Parameters here: [http://support.google.com/analytics/bin/answer.py?hl=en&answer=1033867](http://support.google.com/analytics/bin/answer.py?hl=en&answer=1033867)

Example URL Format: http://yourdomain.com/yourpage/?utm_source=testSource&utm_medium=testMedium&utm_term=testTerm&utm_content=testContent&utm_campaign=testName




