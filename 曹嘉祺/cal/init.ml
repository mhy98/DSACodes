(def ssPoly (arg POLY p FLOAT a FLOAT b) (multi (let ps (sPoly p)) (let aa (calPoly ps a)) (let bb (calPoly ps b)) (print (sub bb aa)) (br) (delElem ps) (delElem aa) (delElem bb)))
(def printToZero (arg INT a) (multi (let tmp a) (for (bigger tmp 0) (multi (print tmp) (br) (let tmp (sub tmp 1)))) (delElem tmp)))
#end
