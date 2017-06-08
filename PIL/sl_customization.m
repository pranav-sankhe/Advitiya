sl_customization_path = fullfile('/media','pranav','Common_space2','projects','advitiya','PIL');

if strfind(path,sl_customization_path)
    rmpath(sl_customization_path)
end

sl_refresh_customizations
currentDir = pwd;
rtwdemodir();
FileData = load('FileName.mat');
csvwrite('FileName.csv', FileData.M);