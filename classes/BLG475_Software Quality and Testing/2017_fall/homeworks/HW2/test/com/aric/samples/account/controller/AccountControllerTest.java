package com.aric.samples.account.controller;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.web.servlet.MockMvc;

import static org.hamcrest.CoreMatchers.containsString;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.get;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.post;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.content;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

@RunWith(SpringRunner.class)
@SpringBootTest
@AutoConfigureMockMvc
public class AccountControllerTest {

    @Autowired
    private MockMvc server;

    @Before
    public void initializeData() throws Exception{
            this.server.perform(post("/account").content("{\n" +
                    "\t\"balance\": 43350.0,\n" +
                    "\t\"ownerTckn\":124,\n" +
                    "\t\"ownerFirstName\": \"Mehmet\",\n" +
                    "\t\"ownerLastName\": \"Yar\"\n" +
                    "}"));
            this.server.perform(post("/account").content("{\n" +
                    "\t\"balance\": 64561.0,\n" +
                    "\t\"ownerTckn\":354,\n" +
                    "\t\"ownerFirstName\": \"Clark\",\n" +
                    "\t\"ownerLastName\": \"Kent\"\n" +
                    "}"));
    }

    @Test
    public void findbyTckno_shouldReturnFoundAccount() throws Exception {
        this.server.perform(get("/query").param("tckn","124"))
                .andExpect(content().string(containsString("{\"id\":1,\"balance\":43300.0,\"ownerTckn\":124,\"ownerFirstName\":\"Mehmet\",\"ownerLastName\":\"Yar\"}")))
                .andExpect(status().isOk());
    }

    @Test
    public void findbyTckno_withNoParams_shouldReturnHttp400() throws Exception {
        this.server.perform(get("/query"))
                .andExpect(status().isBadRequest());
    }

    @Test
    public void findbyTckno_withNonExistingParams_shouldReturnEmptyArray() throws Exception {
     this.server.perform(get("/query").param("tckn","4242"))
            .andExpect(content().json("[]"))
            .andExpect(status().isOk());
    }

    @Test
    public void depositTest() throws Exception{
        this.server.perform(get("/deposit")
                .param("id","1")
                .param("amount","100"))
                .andExpect(status().isOk());
        this.server.perform(get("/query").param("tckn","124"))
                .andExpect(content().string(containsString("{\"id\":1,\"balance\":43400.0,\"ownerTckn\":124,\"ownerFirstName\":\"Mehmet\",\"ownerLastName\":\"Yar\"}")))
                .andExpect(status().isOk());
    }

    @Test
    public void depositTestWithNoParamsExpectHttp200() throws Exception{
        this.server.perform(get("/deposit"))
                .andExpect(status().isBadRequest());
    }

    @Test
    public void eftTest() throws Exception{
        this.server.perform(get("/eft")
                .param("senderId","1")
                .param("receiverId","2")
                .param("amount","50"))
                .andExpect(status().isOk());
        this.server.perform(get("/query").param("tckn","124"))
                .andExpect(content().string(containsString("{\"id\":1,\"balance\":43300.0,\"ownerTckn\":124,\"ownerFirstName\":\"Mehmet\",\"ownerLastName\":\"Yar\"}")))
                .andExpect(status().isOk());
        this.server.perform(get("/query").param("tckn","354"))
                .andExpect(content().string(containsString("{\"id\":2,\"balance\":64611.0,\"ownerTckn\":354,\"ownerFirstName\":\"Clark\",\"ownerLastName\":\"Kent\"}")))
                .andExpect(status().isOk());

    }

    @Test
    public void eftTestWithNoParamsExpectHttp200() throws Exception{
        this.server.perform(get("/eft"))
                .andExpect(status().isBadRequest());
    }

}