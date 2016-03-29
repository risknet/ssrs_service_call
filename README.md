# ssrs_service_call

These days, generating and running your business report has become an easy task by using Microsoft SSRS. Once you finish building your own report, you can run it from the web browser inside of your network or you can code your application to export the report to any format.  Since I kept getting this same question from friends and colleagues over and over, here I am posting the simple "How To." The same article is available in my blog, www.risknetlee.com, as well.


1. Setting up the web reference in Visual Studio to call SSRS webservice. In my application, I was using SSRS 2010 report server along with 2005 SSRS report execution server.
2. Call the procedure with the right parameter name and its value. When calling the procedure, the report parameter name must be the one you are using in **Name** field inside your SSRS report. 

