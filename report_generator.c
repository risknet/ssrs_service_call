
// I am using the hashtable to pass "report parameter & value" pair
// If you have more than one report to run, call this procedure inside a loop of "reports"
public void Rpt_GenerateReport(string reportLocation, Hashtable userParamValues, string targetLocationFile, string renderingFormat)
        {
            SSRS.ReportingService2010 rptService = new SSRS.ReportingService2010();
            SSRSExec.ReportExecutionService rptExecute = new SSRSExec.ReportExecutionService();

            // rptService.UseDefaultCredentials = true;
            rptService.Credentials = System.Net.CredentialCache.DefaultCredentials;
            rptService.Timeout = 3000000;
            rptExecute.Credentials = System.Net.CredentialCache.DefaultCredentials;
            rptExecute.Timeout = 3000000;

            try
            {
                // run for each report
                // these variables are only for temporary usage here
                bool forRendering = true;
                string historyId = null;
                string encoding;
                string mimeType;
                string extention;
                string[] streamIDs;
                SSRS.ParameterValue[] parameterValues = null;
                SSRS.DataSourceCredentials[] dataCredentials = null;
                SSRS.ItemParameter[] itemParameters = null;
                SSRSExec.ParameterValue[] execParameterValues = null;
                SSRSExec.Warning[] warnings;

                // load the report first
                ExecutionInfo execInfo = rptExecute.LoadReport(reportLocation, null);

                // the next block of codes will get a set of real parameters from a given report and
                // assign user's defined parameter value to the parameter
                itemParameters = rptService.GetItemParameters(reportLocation,
                                                              historyId,
                                                              forRendering,
                                                              parameterValues,
                                                              dataCredentials);
                // initialize execParameterValues for this report
                execParameterValues = new SSRSExec.ParameterValue[itemParameters.Count()];
                int paramIndex = 0;

                if (itemParameters != null)
                {
                    // this report needs a report parameter & its value
                    // assign a value to the report parameter 
                    foreach (ItemParameter param in itemParameters)
                    {
                        SSRSExec.ParameterValue assignThis = new SSRSExec.ParameterValue();
                        assignThis.Label = param.Name;
                        assignThis.Name = param.Name;
                        assignThis.Value = userParamValues[param.Name].ToString();
                        execParameterValues[paramIndex++] = assignThis;
                    }
                    rptExecute.SetExecutionParameters(execParameterValues, "en-us");
                }

                // start rendering a report
                byte[] reportBytes = rptExecute.Render(renderingFormat,   // report output format
                                                        null,
                                                        out extention,
                                                        out mimeType,
                                                        out encoding,
                                                        out warnings,
                                                        out streamIDs);
                // write output to the targetLocationFile
                using (FileStream fileStream = File.OpenWrite(targetLocationFile))
                {
                    fileStream.Write(reportBytes, 0, reportBytes.Length);
                }
            }
            catch (Exception e)
            {
                throw e;
            }
            finally
            {
                rptService.Dispose();
                rptExecute.Dispose();
            }
        }