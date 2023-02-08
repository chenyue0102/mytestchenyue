function onClickDelete2(id, name){
    var tip = "确认删除" + name + "?"
    var f = confirm(tip)
    if (f){
        alert(tip)
    }
}