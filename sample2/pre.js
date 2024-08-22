Module.noExitRuntime = true;

Module['postRun'] = () => {
    let blob = FS.readFile("result.png");
    let file = new File([blob], "result.png");
    console.log(blob);

    let img = new Image();

    img.onload = (e) => {
        const canvas = document.getElementById("canvas");
        const ctx = canvas.getContext("2d");
        
        canvas.width = img.width;
        canvas.height = img.height;
        ctx.width = img.width;
        ctx.height = img.height;

        ctx.drawImage(img, 0, 0);
    };

    img.src = URL.createObjectURL(file);

};
