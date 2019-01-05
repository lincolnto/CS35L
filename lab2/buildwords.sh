#!/bin/bash                                               
                                                          
# Remove text before and after table                      
sed '/<!DOCTYPE/,/<\/font><\/td>/d' |                     
sed '/<\/table>/,/<\/html>/d' |                           
                                                          
# Remove English word entries                             
sed '/<tr>/,/<\/td>/d' |                                  
                                                          
# Set all characters to lower                             
tr '[:upper:]' '[:lower:]' |                              
                                                          
# Replace ` with '                                        
sed s/\`/\'/g |                                           
                                                          
# Fix underlined characters                               
sed 's/<u>a<\/u>/a/g' |                                   
sed 's/<u>e<\/u>/e/g' |                                   
sed 's/<u>i<\/u>/i/g' |                                   
sed 's/<u>o<\/u>/o/g' |                                   
sed 's/<u>u<\/u>/u/g' |                                   
                                                          
# Cleanup: Remove Carriage returns                        
tr -d '\r\n' |                                            
                                                          
# Cleanup: Remove closing </td> tags, replace with newline
sed 's/<\/td>/\n/g' |                                     
                                                          
# Cleanup: Remove commas, replace with newline            
sed 's/\,/\n/g' |                                         
                                                          
# Cleanup: Remove leftover HTML tags                      
sed 's/<[^>]*>//g' |                                      
                                                          
# Cleanup: Replace spaces with newline                    
sed 's/ /\n/g' |                                          
                                                          
# Cleanup: Remove extra spaces                            
tr -d '[:blank:]' |                                       
                                                          
# Delete any words containing a -                         
sed '/-/d' |                                              
                                                          
# Spellchecking                                           
tr -cs "pk\'mnwlhaeiou<" '[\n*]' |                        
                                                          
# Sort and remove duplicates                              
sort -u |                                                 
                                                          
# Remove leftover empty lines                             
sed '/^$/d'      